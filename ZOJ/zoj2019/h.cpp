#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int pre[maxn];
int find(int x) {
    return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return ;
    pre[x] = y;
}

vector<int> edge[maxn];
int n, m, q;

int cnt, bel[maxn]; // important!
namespace Tarjan {
    int tot, dfn[maxn], low[maxn], st[maxn], top, vis[maxn];
    void clear(int n) {
        tot = top = cnt = 0;
        for (int i = 1; i <= n; i++) {
            edge[i].clear(); dfn[i] = vis[i] = bel[i] = 0;
        }
    }
    void dfs(int u, int f) {
        dfn[u] = low[u] = ++tot;
        st[++top] = u; vis[u] = 1;
        int k = 0;
        for (int& v: edge[u]) {
            if (v == f && !k) {
                k++; continue;
            } 
            if (!dfn[v]) {
                dfs(v, u); low[u] = min(low[u], low[v]);
            } else if (vis[v]) low[u] = min(low[u], dfn[v]);
        }
        if (dfn[u] == low[u]) {
            cnt++; int t = 0;
            do {
                t = st[top--];
                bel[t] = cnt;
                vis[t] = 0;
            } while (t != u);
        }
    }
    void scc(int n, vector<int> * g) {
        for (int i = 1; i <= n; i++) if (!dfn[i]) Tarjan::dfs(i, 0);
        for (int i = 1; i <= n; i++) g[i].clear();
        for (int i = 1; i <= n; i++) {
            int u = bel[i];
            for (int& x: edge[i]) {
                int v = bel[x];
                if (u != v) {
                    g[u].push_back(v);
                }
            }
        }
    }
}

namespace Tree {
    vector<int> block[maxn];
    int tin[maxn], tout[maxn], vis[maxn], tot;
    int dp[maxn][22], dep[maxn];
    void dfs(int u, int fa){
        tin[u] = ++tot; 
        vis[u] = 1;
        dp[u][0] = fa; 
        dep[u] = dep[fa] + 1;
        for (int& v: block[u]) {
            if (v == fa) continue;
            dfs(v, u);
        }
        tout[u] = tot;
    }
    int qlca(int x, int y){
        if (dep[x] < dep[y]) swap(x, y);
        int tmp = dep[x] - dep[y];
        for (int i = 0; tmp; i++, tmp >>= 1)
            if (tmp & 1) x = dp[x][i];
        if (x == y) return x;
        for (int i = 20; i >= 0; i--){
            if (dp[x][i] != dp[y][i]){
                x = dp[x][i]; y = dp[y][i];
            }
        }
        return dp[x][0];
    }
    void init() {
        for (int i = 0; i <= cnt; i++) {
            vis[i] = 0; ms(dp[i], 0);
        }
        dep[0] = tot = 0;
        for (int i = 1; i <= cnt; i++) if (!vis[i]) {
            dfs(i, 0);
        }
        for (int j = 1; j < 20; j++) 
            for (int i = 1; i <= cnt; i++) 
                dp[i][j] = dp[dp[i][j - 1]][j - 1];
    }
    int check(int p, int u) {
        return tin[p] <= tin[u] && tout[p] >= tout[u];
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &q); 
        Tarjan::clear(n);
        for (int i = 1; i <= n; i++) {
            pre[i] = i;
        }
        for (int i = 1, u, v; i <= m; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v); edge[v].push_back(u);
            join(u, v);
        }
        Tarjan::scc(n, Tree::block);
        Tree::init();
        while (q--) {
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            if (find(u) != find(v) || find(u) != find(w)) {
                puts("No"); continue;
            }
            u = bel[u]; v = bel[v]; w = bel[w];
            int g = Tree::qlca(v, w);
            if (Tree::check(g, u)) {
                if (Tree::check(u, v) || Tree::check(u, w)) puts("Yes");
                else puts("No");
            } else puts("No");
        }
    }
    return 0;
}