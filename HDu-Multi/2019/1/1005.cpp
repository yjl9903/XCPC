#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
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
typedef pair<int,int> PII;
const int mod = 998244353;
const ll inf = 1ll << 61;
const int maxn = 100000 + 5;

struct E {
    int u, v, c;
} eg[maxn];

int n, m;
vector<PII> edge[maxn];

int vis[maxn];
ll dis1[maxn], dis2[maxn];
void dij(int s, ll* dis) {
    for (int i = 1; i <= n; i++) vis[i] = 0, dis[i] = inf;
    priority_queue< pair<ll,int> > q; q.push({ 0, s }); dis[s] = 0;
    while (!q.empty()) {
        PII x = q.top(); q.pop();
        int u = x.second;
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto& x: edge[u]) {
            int v = x.first;
            if (dis[v] > dis[u] + x.second) {
                dis[v] = dis[u] + x.second;
                q.push({ -dis[v], v });
            }
        }
    }
}

struct Edge {
    int from, to; ll cap, flow;
    Edge(int u, int v, ll c, ll f): from(u), to(v), cap(c), flow(f) {}
};

struct Dinic {
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[maxn];
    bool vis[maxn];
    int dep[maxn], cur[maxn];
    void init(int n) {
        this->n = n;
        for (int i = 0; i <= n; i++) G[i].clear();
        edges.clear();
    }
    void adde(int from, int to, ll cap) {
        edges.emplace_back(from, to, cap, 0);
        edges.emplace_back(to, from, 0, 0);
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }
    bool bfs() {
        ms(vis, 0); ms(dep, 0);
        queue<int> q; q.push(s);
        dep[s] = 0; vis[s] = 1;
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int i = 0; i < G[x].size(); i++) {
                Edge& e = edges[G[x][i]];
                if (!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = 1;
                    dep[e.to] = dep[x] + 1;
                    q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    ll dfs(int x, ll a) {
        if (x == t || a == 0) return a;
        ll flow = 0, f;
        for (int& i = cur[x]; i < G[x].size(); i++) { 
            Edge& e = edges[G[x][i]];
            if (dep[x] + 1 == dep[e.to] && (f = dfs(e.to, min(a, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }
    ll get(int s, int t) {
        this->s = s, this->t = t;
        ll flow = 0;
        while (bfs()) {
            ms(cur, 0);
            flow += dfs(s, inf);
        }
        return flow;
    }
} f;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) edge[i].clear();
        for (int i = 1, u, v, c; i <= m; i++) {
            scanf("%d%d%d", &u, &v, &c);
            eg[i].u = u; eg[i].v = v; eg[i].c = c;
            edge[u].push_back({v, c});
        }
        dij(1, dis1); 
        for (int i = 1; i <= n; i++) edge[i].clear();
        for (int i = 1; i <= m; i++) {
            edge[eg[i].v].push_back({eg[i].u, eg[i].c});
        }
        dij(n, dis2);
        f.init(n);
        ll len = dis1[n];
        if (len == inf) {
            puts("0"); continue;
        }
        for (int i = 1; i <= m; i++) {
            int u = eg[i].u, v = eg[i].v;
            ll c = eg[i].c;
            if (dis1[u] + dis2[v] + c == len) {
                f.adde(u, v, c);
            } else if (dis1[v] + dis2[u] + c == len) {
                f.adde(v, u, c);
            }
        }
        printf("%lld\n", f.get(1, n));
    }
    return 0;
}