#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

vector<int> edge[maxn];
int n, q, in[maxn], out[maxn];

namespace hld {
    int dep[maxn], fa[maxn], siz[maxn], son[maxn], top[maxn], tot;
    void dfs(int u, int f) {
        dep[u] = dep[f] + 1; fa[u] = f; siz[u] = 1;
        in[u] = ++tot; int m = -1;
        for (int& v: edge[u]) {
            if (v == f) continue;
            dfs(v, u);
            siz[u] += siz[v];
            if (siz[v] > m) son[u] = v, m = siz[v];
        }
        out[u] = tot;
    }
    void dfs(int u, int f, int tp) {
        top[u] = tp;
        if (!son[u]) return;
        dfs(son[u], u, tp);
        for (int& v: edge[u]) {
            if (v == f || v == son[u]) continue;
            dfs(v, u, v);
        }
    }
    void init() {
        dfs(1, 0); dfs(1, 0, 1);
    }
    int qlca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
};

int tree[maxn];
inline int lowbit(int x) { return x & -x; }
inline void update(int i, int x) {
    while (i < maxn) {
        tree[i] += x; i += lowbit(i);
    }
}
inline void update(int L, int R, int x) {
    update(L, x); update(R + 1, -x);
}
inline int query(int i) {
    int r = 0;
    while (i > 0) { r += tree[i]; i -= lowbit(i); }
    return r;
}

ll dp[maxn];
int a[maxn], f[maxn], mark[maxn];

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    } hld::init();
    int k, m, r;
    while (q--) {
        scanf("%d%d%d", &k, &m, &r);
        for (int i = 1; i <= k; i++) {
            scanf("%d", a + i);
            update(in[a[i]], out[a[i]], 1);
            mark[a[i]] = 1;
        }
        for (int i = 1; i <= k; i++) {
            int lca = hld::qlca(a[i], r);
            f[i] = query(in[a[i]]) + query(in[r]) - 2 * query(in[lca]) + mark[lca] - 1;
        } 
        sort(f + 1, f + k + 1);
        dp[0] = 1;
        for (int i = 1; i <= k; i++) {
            for (int j = m; j >= 0; j--) {
                if (j <= f[i]) dp[j] = 0;
                else dp[j] = (dp[j - 1] + 1ll * (j - f[i]) * dp[j] % mod) % mod;
            }
        }
        ll ans = 0;
        for (int i = 1; i <= m; i++) ans = (ans + dp[i]) % mod, dp[i] = 0; 
        printf("%I64d\n", ans);
        for (int i = 1; i <= k; i++) {
            update(in[a[i]], out[a[i]], -1);
            mark[a[i]] = 0;
        }
    }
    return 0;
}