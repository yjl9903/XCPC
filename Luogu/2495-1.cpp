#include<bits/stdc++.h>
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
using namespace std;
typedef long long ll;
const int max_n = 500005;
struct edge {
    int u, v, w, next;
}G[max_n * 2];
int head[max_n], tot;
void add_edge(int u, int v, int w) {
    G[tot] = {u, v, w, head[u]};
    head[u] = tot++;
}
int dfn[max_n], nt, dep[max_n], par[max_n][20];
void init(int n) {
    tot = 2; for(int i = 0; i <= n; i++) head[i] = 0;
    nt = 0;
}
ll val[max_n];
void dfs(int u, int fa) {
    dfn[u] = ++nt;
    dep[u] = dep[fa] + 1;
    par[u][0] = fa;
    for(int j = 1; j <= 19; j++) par[u][j] = par[par[u][j - 1]][j - 1];
    for(int i = head[u]; i; i = G[i].next) {
        int v = G[i].v, w = G[i].w;
        if(v == fa) continue;
        val[v] = min(val[u], w * 1ll);
        dfs(v, u);
    }
}
int LCA(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 19; i >= 0; i--) if((dep[u] - dep[v]) >> i & 1) u = par[u][i];
    if(u == v) return u;
    for(int i = 19; i >= 0; i--) if(par[u][i] != par[v][i]) u = par[u][i], v = par[v][i]; 
    return par[u][0];
}
vector<int> adj[max_n];
int stk[max_n], top;
bool key[max_n];
ll solve(vector<int> vec, int rt) {
    sort(vec.begin(), vec.end(), [&] (int x, int y) {return dfn[x] < dfn[y];});
    top = 0; stk[++top] = rt;
    auto insert = [&] (int x) {
        if(top == 1) stk[++top] = x;
        else {
            int u = stk[top];
            dbg(u, x);
            int lca = LCA(u, x);
            // if(lca == u) stk[++top] = x;
            if(lca == u) {
              dbg("in");
              return ;
            }
            else {
                while(top > 1 && dfn[stk[top - 1]] >= dfn[lca]) {
                    adj[stk[top - 1]].push_back(stk[top]);
                    top --;
                }
                if(lca != stk[top]) {
                    adj[lca].push_back(stk[top]);
                    stk[top] = lca;
                }
                stk[++top] = x;
            }
        }
    };
    for(auto x : vec) insert(x) ,key[x] = true;
    while(top > 1) adj[stk[top - 1]].push_back(stk[top]), top--;
    function<ll(int)> dfs = [&] (int u) {
      dbg(u);
        if(adj[u].size() == 0) {
            if(key[u]) return val[u];
            else return 0ll;
        }
        ll res = 0;
        for(auto v : adj[u]) {
            res += dfs(v);
        }
        if(key[u]) res = val[u];
        else res = min(res, val[u]);
        adj[u].clear(), key[u] = false;
        return res;
        /*
        ll res = 0;
        for(auto v : adj[u]) {
            res += min(val[v], dfs(v));
        }
        if(key[u]) res = val[u];
        adj[u].clear(); key[u] = false;
        return res;
        */
    };
    return dfs(rt);
}
int n, m;
int main() {
    scanf("%d", &n);
    init(n);
    for(int i = 1; i < n; i++) {
        int u, v, w; scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w), add_edge(v, u, w);
    }
    val[1] = 1e18;
    dfs(1, 0);
   // for(int i = 1; i <= n; i++) cout << i << ' ' << val[i] << endl;
    scanf("%d", &m);
    while(m--) {
        int k; scanf("%d", &k);
        vector<int> key(k);
        for(int i = 0; i < k; i++) scanf("%d", &key[i]);
        printf("%lld\n", solve(key,1));
    }
    return 0;
}