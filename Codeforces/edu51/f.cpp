#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
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
typedef pair<int, int> PII;
const int maxn = 100000 + 5;
const ll inf = 1e18;

int n, m, q;

int pre[maxn]; int find(int x){return x == pre[x] ? x : pre[x] = find(pre[x]);}
vector<PII> edge[maxn], g[maxn]; // tree, graph

struct node {
    int v; ll d;
    bool operator<(const node& b) const {
        return d > b.d;
    }
};
ll dis[50][maxn]; bool vis[maxn];
void dijkstra(ll* dis, int st) {
    ms(vis, 0);
    priority_queue<node> q; q.push({st, 0});
    for (int i = 1; i <= n; i++) dis[i] = inf; dis[st] = 0;
    while (!q.empty()) {
        node x = q.top(); q.pop();
        if (vis[x.v]) continue;
        vis[x.v] = 1;
        for (auto& t: g[x.v]) {
            if (dis[t.first] > dis[x.v] + 1ll * t.second) {
                dis[t.first] = dis[x.v] + 1ll * t.second;
                q.push({t.first, dis[t.first]});
            }
        }
    }
}

namespace hld {
    int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
    ll dis[maxn];
    void dfs(int u, int d, int old) {
        dep[u] = d; fa[u] = old; siz[u] = 1;
        int m = -1;
        for (auto& v: edge[u]) {
            if (v.first == fa[u]) continue;
            dis[v.first] = dis[u] + 1ll * v.second;
            dfs(v.first, d + 1, u);
            siz[u] += siz[v.first];
            if (siz[v.first] > m) son[u] = v.first, m = siz[v.first];
        }
    }
    void dfs(int u, int tp) {
        top[u] = tp;
        if (!son[u]) return;
        dfs(son[u], tp);
        for (auto& v: edge[u]) {
            if (v.first == fa[u] || v.first == son[u]) continue;
            dfs(v.first, v.first);
        }
    }
    void init() {
        dfs(1, 1, 0); dfs(1, 1);
    }
    int qlca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] <= dep[v] ? u : v;
    }
    ll qdis(int u, int v) {
        return dis[u] + dis[v] - 2 * dis[qlca(u, v)];
    }
}

int gu[maxn], gv[maxn], gd[maxn];
vector<int> gedge; // not tree edge

int main(){
    scanf("%d%d", &n, &m); 
    for (int i = 0; i <= n; i++) pre[i] = i;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", gu + i, gv + i, gd + i);
        g[gu[i]].push_back({gv[i], gd[i]});
        g[gv[i]].push_back({gu[i], gd[i]});
        int b1 = find(gu[i]), b2 = find(gv[i]);
        if (b1 != b2) {
            edge[gu[i]].push_back({gv[i], gd[i]});
            edge[gv[i]].push_back({gu[i], gd[i]});
            pre[b1] = b2;
        } else {
            gedge.push_back(i);
        }
    } 
    hld::init();
    for (int i = 0; i < gedge.size(); i++) {
        int id = gedge[i];
        dijkstra(dis[2 * i], gu[id]);
        dijkstra(dis[2 * i + 1], gv[id]);
    }

    scanf("%d", &q); int qu, qv;
    while (q--) {
        scanf("%d%d", &qu, &qv);
        ll ans = hld::qdis(qu, qv);
        for (int i = 0; i < gedge.size(); i++) {
            int id = gedge[i];
            ans = min(ans, gd[id] + min(dis[2 * i][qu] + dis[2 * i + 1][qv], dis[2 * i][qv] + dis[2 * i + 1][qu]));
        }
        printf("%I64d\n", ans);
    }
    return 0;
}