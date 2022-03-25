#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
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
const int maxn = 300000 + 5;

int n, q, dfn[maxn], key[maxn], tot;
vector<PII> edge[maxn];

namespace LCA {
    int fa[maxn][20], dep[maxn], mn[maxn][20];
    void dfs(int u, int f) {
        dfn[u] = ++tot; fa[u][0] = f; dep[u] = dep[f] + 1;
        for (int i = 1; i < 20; i++) {
            fa[u][i] = fa[fa[u][i - 1]][i - 1];
            mn[u][i] = min(mn[u][i - 1], mn[fa[u][i - 1]][i - 1]);
        }
        for (auto& x: edge[u]) {
            int v = x.first;
            if (v == f) continue;
            mn[v][0] = x.second;
            dfs(v, u);
        }
    }
    PII qlca(int u, int v) {
        int d = inf;
        if (dep[u] < dep[v]) swap(u, v);
        for (int i = 19; i >= 0; i--) if (dep[fa[u][i]] >= dep[v]) {
            d = min(d, mn[u][i]); u = fa[u][i];
        }
        if (u == v) return { u, d };
        for (int i = 19; i >= 0; i--) {
            if (fa[u][i] == fa[v][i]) continue;
            d = min(d, min(mn[u][i], mn[v][i]));
            u = fa[u][i]; v = fa[v][i];
        }
        return { fa[u][0], d };
    }
}

ll f[maxn];
ll dp(int u, int ff, ll w) {
    dbg(u);
    if (key[u]) return w;
    ll res = 0;
    for (auto& x: edge[u]) {
        int v = x.first;
        res += dp(v, u, min(w, 1ll * x.second));
    }
    // if (u == 1) return res;
    return min(res, w);
}
namespace VT {
    int stk[maxn], top;
    void build(vector<int>& vec) {
        sort(vec.begin(), vec.end(), [](int a, int b) { return dfn[a] < dfn[b]; });
        stk[top = 1] = 1; edge[1].clear();
        for (int x: vec) {
            if (x == 1) continue;
            int g = LCA::qlca(stk[top], x).first;
            if (g != stk[top]) {
                while (dfn[g] < dfn[stk[top - 1]]) {
                    int w = LCA::qlca(stk[top], stk[top - 1]).second;
                    edge[stk[top - 1]].push_back({ stk[top], w }); top--;
                }
                int w = LCA::qlca(g, stk[top]).second;
                if (dfn[g] > dfn[stk[top - 1]]) {
                    edge[g].clear();
                    edge[g].push_back({ stk[top], w }); 
                    stk[top] = g;
                } else {
                    edge[g].push_back({ stk[top], w });
                    top--;
                }
            }
            edge[x].clear(); stk[++top] = x;
        }
        for (int i = 1; i < top; i++) {
            int w = LCA::qlca(stk[i], stk[i + 1]).second;
            edge[stk[i]].push_back({ stk[i + 1], w });
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2, u, v, w; i <= n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        edge[u].push_back({v, w}); edge[v].push_back({u, w});
    } 
    LCA::dfs(1, 0);
    scanf("%d", &q);
    while (q--) {
        int k; vector<int> vec;
        scanf("%d", &k);
        for (int i = 1, x; i <= k; i++) {
            scanf("%d", &x); 
            vec.push_back(x);
            key[x] = 1;
        }
        VT::build(vec);
        // dp(1, 0); printf("%lld\n", f[1]);
        printf("%lld\n", dp(1, 0, 1e18));
        for (int x: vec) key[x] = 0;
    }
    return 0;
}