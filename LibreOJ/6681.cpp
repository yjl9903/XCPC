#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 50000 + 5;
const int seed = 53;
const int p1 = 1e9 + 7, p2 = 1e9 + 9;

int n, vis[maxn], siz[maxn], mn, rt, sum;
ll ans;
vector<PII> edge[maxn];

void getrt(int u, int f) {
    siz[u] = 1; int m = 0;
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f || vis[v]) continue;
        getrt(v, u);
        siz[u] += siz[v];
        m = max(m, siz[v]);
    }
    m = max(m, sum - siz[u]);
    if (m < mn) {
        mn = m; rt = u;
    }
}
int getrt(int u) {
    sum = siz[u]; mn = 1e9;
    getrt(u, 0); return rt;
}

struct Border {
    int l, r, d;
};

struct Query {
    int b, r, id, sgn;
};

struct DS {
    int n, B, a[250][250], b[maxn];
    void set(int nn) {
        n = nn; B = sqrt(n);
    }
    void update(int l, int x) {
        for (int i = 1; i <= B; i++) {
            a[i][l % i] += x;
        }
        b[l] += x;
    }
} g;

namespace acam {
    int sz, ch[maxn][26], fail[maxn];
    int cnt[maxn], len[maxn], ans[maxn];
    vector<Border> bds[maxn];
    vector<Query> que[maxn];
    vector<int> fG[maxn];
    int node(int l) {
        ms(ch[++sz], 0); 
        len[sz] = l;
        fail[sz] = cnt[sz] = ans[sz] = 0;
        fG[sz].clear(); bds[sz].clear(); que[sz].clear();
        return sz;
    }
    void clear() {
        sz = 0; node(0);
        for (int i = 0; i < 26; i++) ch[0][i] = 1;
    }
    void build() {
        queue<int> q; q.push(1);
        while (!q.empty()) {
            int t = q.front(); q.pop();
            for (int i = 0; i < 26; i++) {
                if (ch[t][i]) {
                    fail[ch[t][i]] = ch[fail[t]][i];
                    q.push(ch[t][i]);
                } else {
                    ch[t][i] = ch[fail[t]][i];
                }
            }
        }
        for (int i = 2; i <= sz; i++) fG[fail[i]].push_back(i);
    }

    vector<int> stk;
    int get(int x) {
        int l = 0, r = (int)stk.size() - 1, ans = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            if (len[stk[m]] <= x) ans = stk[m], l = m + 1;
            else r = m - 1;
        }
        return ans;
    }
    void dfs(int u) {
        stk.push_back(u);
        g.update(len[u], cnt[u]);
        for (auto& x: bds[u]) {
            if (x.d <= g.B) {
                int a = get(len[u] - x.r - 1);
                int b = get(len[u] - x.l);
                if (a > 0) que[a].push_back({ x.d, (len[u] - x.l) % x.d, u, -1 });
                if (b > 0) que[b].push_back({ x.d, (len[u] - x.l) % x.d, u, +1 });
            } else {
                for (int i = x.l; i <= x.r; i += x.d) {
                    ans[u] += g.b[len[u] - i];
                }
            }
        }
        for (int v: fG[u]) dfs(v);
        for (auto& q: que[u]) {
            ans[q.id] += q.sgn * g.a[q.b][q.r];
        }
        que[u].clear();
        g.update(len[u], -cnt[u]);
        stk.pop_back();
    }
}
using acam::ch;
using acam::len;
using acam::node;

void predfs(int u, int f, int nd) {
    acam::cnt[nd]++;
    for (auto& x: edge[u]) {
        int v = x.first, w = x.second;
        if (v == f || vis[v]) continue;
        if (!ch[nd][w]) {
            ch[nd][w] = node(len[nd] + 1);
        }
        predfs(v, u, ch[nd][w]);
    }
}
ull xp1[maxn], xp2[maxn];
void dfs(int u, ull h1, ull h2, ull h3, ull h4, vector<Border> vec) {
    for (int i = 0; i < 2; i++) {
        if (!ch[u][i]) continue;
        int v = ch[u][i];
        ull nh1 = (h1 + xp1[len[u]] * i) % p1;
        ull nh2 = (h2 * seed + i) % p1;
        ull nh3 = (h3 + xp2[len[u]] * i) % p2;
        ull nh4 = (h4 * seed + i) % p2;
        acam::bds[v] = vec;
        if (nh1 == nh2 && nh3 == nh4) {
            auto& bd = acam::bds[v];
            if (bd.empty()) {
                bd.push_back({ len[v], len[v], len[v] });
            } else {
                Border& back = bd.back();
                if (len[v] - back.r == back.d) back.r = len[v];
                else {
                    bd.push_back({ len[v], len[v], len[v] - back.r });
                }
            }
        }
        dfs(v, nh1, nh2, nh3, nh4, acam::bds[v]);
    }
}
ll cal(int u, int f) {
    acam::clear();
    ll ans = 0;
    if (f == -1) {
        predfs(u, 0, 1);
    } else {
        ch[1][f] = node(1);
        predfs(u, 0, ch[1][f]);
    }
    dfs(1, 0, 0, 0, 0, vector<Border>(0));
    acam::build(); 
    g.set(siz[u]);
    acam::dfs(1);
    auto C = [](int n) -> ll {
        return 1ll * n * (n - 1) / 2;
    };
    for (int i = 2; i <= acam::sz; i++) {
        ans += 1ll * acam::cnt[i] * acam::ans[i] + C(acam::cnt[i]);
    }
    return ans;
}
void solve(int u) {
    vis[u] = 1;
    ans += cal(u, -1);
    for (auto& x: edge[u]) {
        int v = x.first;
        if (vis[v]) continue;
        ans -= cal(v, x.second);
        solve(getrt(v));
    }
}

int main() {
    scanf("%d", &n);
    xp1[0] = xp2[0] = 1;
    for (int i = 1; i < maxn; i++) {
        xp1[i] = xp1[i - 1] * seed % p1;
        xp2[i] = xp2[i - 1] * seed % p2;
    }
    for (int i = 1, u, v, w; i < n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        edge[u].push_back({v, w});
        edge[v].push_back({u, w});
    }
    siz[1] = n;
    solve(getrt(1));
    cout << ans;
    return 0;
}