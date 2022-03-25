#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
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
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, ringsz;
vector<int> edge[maxn];

int fa[maxn], vis[maxn], ring[maxn];
vector<int> onring;
void getring(int u, int f) {
    fa[u] = f;
    vis[u] = 1;
    for (int& v: edge[u]) {
        if (v == f) continue;
        if (vis[v]) {
            if (!onring.empty()) continue;
            onring.push_back(v);
            int x = u;
            while (x != v) {
                onring.push_back(x); x = fa[x];
            }
            continue;
        }
        getring(v, u);
    }
    vis[u] = 0;
}
int mxd = 0, p = 0;
int dfs(int u, int f, int d) {
    if (d > mxd) {
        mxd = d; p = u;
    } else if (d == mxd) {
        p = min(p, u);
    }
    int s = 1;
    for (int& v: edge[u]) {
        if (v == f) continue;
        if (ring[u] && ring[v]) continue;
        s += dfs(v, u, d + 1);
    }   
    return s;
}

vector<int> siz, dia;
vector<PII> ed, diaed;
PII info[maxn << 2];
PII join(PII a, PII b) {
    if (a.first > b.first) return a;
    else if (a.first < b.first) return b;
    else if (ed[a.second].second < ed[b.second].second) return a;
    return b;
}
void pushup(int rt) {
    info[rt] = join(info[rt << 1], info[rt << 1 | 1]);
}
void build(int l, int r, int rt) {
    if (l == r) {
        int x = l; if (x >= ringsz) x -= ringsz;
        info[rt] = { ed[x].first - l, x };
        return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
    pushup(rt);
}
PII query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) return info[rt];
    int m = (l + r) / 2;
    PII ans = { -inf, -inf };
    if (L <= m) ans = query(L, R, lson);
    if (R > m) ans = join(ans, query(L, R, rson));
    return ans;
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v); edge[v].push_back(u);
        }
        getring(1, 0);
        for (int x: onring) ring[x] = 1;
        int allsz = 0;
        ringsz = (int)onring.size();
        for (int x: onring) {
            mxd = -1; p = 0;
            int s = dfs(x, 0, 0);
            allsz += 2 * (s - 1);
            siz.push_back(s);
            ed.push_back({mxd, p});
            int p1 = p;
            mxd = -1; p = 0;
            dfs(p1, 0, 0);
            dia.push_back(mxd);
            diaed.push_back({p, p1});
        }
        int dis = 2 * n, s = inf, t = inf;
        auto merge = [&](int a, int b, int c) {
            if (a < dis) {
                dis = a; s = min(b, c); t = max(b, c);
            } else if (a == dis) {
                if (b > c) swap(b, c);
                if (b < s) s = b, t = c;
                else if (b == s) t = min(c, t);
            }
        };
        for (int i = 0; i < ringsz; i++) {
            int tot = ringsz + allsz - dia[i];
            merge(tot, diaed[i].first, diaed[i].second);
        }
        build(0, 2 * ringsz - 1, 1);
        for (int i = 0; i < ringsz; i++) {
            PII qans = query(i + 1, i + ringsz - 1, 0, 2 * ringsz - 1, 1);
            int tot = ringsz + allsz - 2;
            tot -= ed[i].first + qans.first + i;
            int a = ed[i].second, b = ed[qans.second].second;
            merge(tot, a, b);
        }
        printf("Case #%d: %d %d %d\n", ++kase, dis, s, t);
        onring.clear();
        siz.clear(); dia.clear();
        ed.clear(); diaed.clear();
        for (int i = 1; i <= n; i++) {
            edge[i].clear();
            ring[i] = vis[i] = fa[i] = 0;
        }
    }
    return 0;
}