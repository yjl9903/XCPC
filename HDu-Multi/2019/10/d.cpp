#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>
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
typedef long long ull;
typedef pair<ll,int> PII;
const int mod = 998244353;
const ll inf = 1ll << 61;
const int maxn = 100000 + 5;

struct LinearBase {
    static const int maxl = 60;
    ll a[maxl + 5];
    int cnt; ull sum = 0;
    void clear() { 
        cnt = 0; sum = 0; ms(a, 0); 
    }
    LinearBase() { clear(); }
    int insert(ll x) {
        ll y = x;
        for (int i = maxl - 1; i >= 0; i--) {
            if (x & (1ll << i)) {
                if (a[i]) x ^= a[i];
                else {
                    a[i] = x; cnt++; sum += y;
                    return true;
                }
            }
        }
        return false;
    }
} lb[maxn << 2];

char s[maxn];
int n, q, pos[maxn];
ll w[maxn];
 
int fa[maxn << 1][21];
namespace sam {
    int tot, last, cnt[maxn << 1];
    int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
    void clear() { 
        tot = last = 1; ms(ch[1], 0);
    }
    int insert(int c) {
        int cur = ++tot, p = last; 
        ms(ch[cur], 0);
        len[cur] = len[last] + 1; 
        cnt[cur] = 1;
        for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
        if (!p) link[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[p] + 1 == len[q]) link[cur] = q;
            else {
                int nq = ++tot; 
                len[nq] = len[p] + 1; 
                cnt[nq] = 0;
                link[nq] = link[q]; 
                link[q] = link[cur] = nq;
                memcpy(ch[nq], ch[q], sizeof ch[q]);
                for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
            }
        }
        return last = cur;
    }
    int c[maxn << 1], a[maxn << 1];
    void rsort() {
        for (int i = 1; i <= tot; i++) c[i] = 0;
        for (int i = 1; i <= tot; i++) c[len[i]]++;
        for (int i = 1; i <= tot; i++) c[i] += c[i - 1];
        for (int i = 1; i <= tot; i++) a[c[len[i]]--] = i;
        for (int i = tot; i; i--) {
            int p = a[i];
            cnt[link[p]] += cnt[p];
        }
    }
    struct Edge {
        int to, nxt;
    } e[maxn << 1];
    int ecnt, head[maxn << 1];
    void adde(int u, int v) {
        e[++ecnt] = { v, head[u] };
        head[u] = ecnt;
    }
    void dfs(int u, int f) {
        fa[u][0] = f;
        for (int i = 1; i < 21; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            dfs(v, u);
        }
    }
    int rk[maxn << 1];
    void build() {
        rsort(); ecnt = 0;
        for (int i = 1; i <= tot; i++) {
            rk[i] = i; head[i] = 0;
            lb[i].clear();
        }
        for (int i = 2; i <= tot; i++) adde(link[i], i);
        dfs(1, 0);
        sort(rk + 1, rk + 1 + tot, [&](int a, int b) {
            return w[cnt[a]] > w[cnt[b]];
        });
        for (int i = 1; i <= tot; i++) {
            int x = rk[i];
            ll val = w[cnt[x]];
            while (x != 1 && lb[x].insert(val)) {
                x = link[x];
            }
        }
    }
}
 
int get(int u, int l) {
    for (int i = 20; i >= 0; i--) {
        if (!fa[u][i]) continue;
        int v = fa[u][i];
        if (sam::len[v] >= l) u = v;
    }
    return u;
}
 
int main() {
    int T; scanf("%d", &T);
    while (T--) {
        sam::clear();
        scanf("%d%s", &n, s + 1);
        for (int i = 1; i <= n; i++) {
            pos[i] = sam::insert(s[i] - 'a');
        }
        for (int i = 1; i <= n; i++) scanf("%lld", w + i);
        sam::build();
        scanf("%d", &q);
        int l, r;
        while (q--) {
            scanf("%d%d", &l, &r);
            int u = get(pos[r], r - l + 1);
            printf("%llu\n", lb[u].sum);
        }
    }
    return 0;
}