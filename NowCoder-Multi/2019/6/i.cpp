#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
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
const int maxn = 100000 + 5;

inline int add(int x, int y) {
    x += y;
    return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
    x -= y;
    return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
    return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
    int r = 1;
    while (n > 0) {
        if (n & 1) r = 1ll * r * x % mod;
        n >>= 1; x = 1ll * x * x % mod;
    }
    return r;
}
inline int inv(int x) {
    return qpow(x, mod - 2);
}

int n, m, ans[maxn];
vector<int> edge[maxn * 2], bcc[maxn];
map<int,int> ew[maxn];

int cnt;
namespace cactus {
    struct E { 
        int to, nxt; 
    } e[maxn * 2];
    int head[maxn], ecnt;
    void adde(int u, int v) {
        e[++ecnt] = {v, head[u]};
        head[u] = ecnt;
    }
    int tot, dfn[maxn], fa[maxn];
    bool ring[maxn];
    void clear(int n) { 
        cnt = ecnt = tot = 0;
        for (int i = 1; i <= n; i++) {
            head[i] = dfn[i] = ans[i] = 0;
        }
    }
    void dfs(int u, int f) {
        dfn[u] = ++tot;
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (v == f) continue;
            if (!dfn[v]) {
                fa[v] = u; ring[u] = false;
                dfs(v, u);
                if (!ring[u]) { 
                    edge[u].push_back(v); edge[v].push_back(u); 
                }
            } else if (dfn[v] < dfn[u]) {
                cnt++; int rt = cnt + n;
                bcc[cnt].clear();
                edge[rt].push_back(v); 
                edge[v].push_back(rt);
                bcc[cnt].push_back(v);
                for (int x = u; x != v; x = fa[x]) {
                    ring[x] = true;
                    bcc[cnt].push_back(x);
                    edge[rt].push_back(x); 
                    edge[x].push_back(rt);
                }
                ring[v] = true;
            }
        }
    }
    void build() {
        dfs(1, 0);
    }
}

void dp(int id) {
    vector<int>& ring = bcc[id];
    int sz = (int)ring.size();
    vector<int> w(sz, 0), pre(sz, 0), suf(sz, 0);
    for (int i = 0; i + 1 < sz; i++) {
        w[i] = ew[ring[i]][ring[i + 1]];
    }
    w[sz - 1] = ew[ring[0]][ring[sz - 1]];
    pre[0] = w[0]; suf[sz - 1] = w[sz - 1];
    for (int i = 1; i < sz; i++) {
        pre[i] = mul(pre[i - 1], w[i]);
    }
    for (int i = sz - 2; i >= 0; i--) {
        suf[i] = mul(suf[i + 1], w[i]);
    }
    int p = ans[ring[0]];
    for (int i = 1; i < sz; i++) {
        int u = ring[i];
        ans[u] = mul(sub(1, pre[i - 1]), sub(1, suf[i]));
        ans[u] = mul(p, sub(1, ans[u]));
    }
}

void dfs(int u, int f) {
    // dbg(u, f);
    if (u > n) dp(u - n);
    for (int v: edge[u]) {
        if (v == f) continue;
        if (u <= n && v <= n) {
            ans[v] = mul(ans[u], ew[u][v]);
        }
        dfs(v, u);
    }
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        cactus::clear(n);
        for (int i = 1; i <= n; i++) ew[i].clear();
        for (int i = 1; i <= 2 * n; i++) edge[i].clear();
        for (int i = 1, u, v, a, b; i <= m; i++) {
            scanf("%d%d%d%d", &u, &v, &a, &b);
            int w = mul(a, inv(b));
            cactus::adde(u, v);
            cactus::adde(v, u);
            ew[u][v] = w;
            ew[v][u] = w;
        }
        cactus::build();
        ans[1] = 1;
        dfs(1, 0);
        int res = 0;
        for (int i = 1; i <= n; i++) res = add(res, ans[i]);
        printf("Case #%d: %d\n", ++kase, res);
    }
    return 0;
}