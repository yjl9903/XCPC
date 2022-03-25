#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const ll inf = 1ll << 60;
const int maxn = 20000 + 5;

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
            //从上次考虑的弧
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

int n, m, d, del[maxn], p[maxn], c[maxn], op[maxn], ans[maxn];
vector<int> num[maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x); num[x].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", c + i);
    }
    scanf("%d", &d);
    for (int i = 1; i <= d; i++) {
        scanf("%d", op + i);
        del[op[i]] = 1;
    }
    for (int i = 1; i <= m; i++) f.adde(0, i, 1);
    for (int i = 1; i <= n; i++) if (!del[i]) {
        f.adde(c[i], m + i, 1);
    }
    int tot = 0, tag = n + m + 5005;
    for (int& x: num[tot]) {
        f.adde(m + x, n + m + 1 + tot, 1);
    }
    f.adde(n + m + 1 + tot, tag, 1);
    for (int i = d; i >= 1; i--) {
        while (f.get(0, tag)) {
            tot++; 
            for (int& x: num[tot]) f.adde(m + x, n + m + 1 + tot, 1);
            f.adde(n + m + 1 + tot, tag, 1);
            // cout << "? " << tot << endl;
        }
        ans[i] = tot;
        f.adde(c[op[i]], m + op[i], 1);
    }
    for (int i = 1; i <= d; i++) printf("%d\n", ans[i]);
    return 0;
}