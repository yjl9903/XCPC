#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <functional>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 10000 + 5;
const int inf = 1000000000 + 7;

int n, m, s, e, k;
// vector<PII> edge[maxn], edge1[maxn];
struct edge{int to, nxt, d;}f[20 * maxn], g[20 * maxn];
int head1[maxn], head2[maxn], tot1, tot2;
void add1(int x, int y, int d){
    f[++tot1] = {y, head1[x], d}; head1[x] = tot1;
}
void add2(int x, int y, int d){
    g[++tot2] = {y, head2[x], d}; head2[x] = tot2;
}

int vis[maxn], dis[maxn];
int dijkstra(int beg = 1){
    ms(vis, 0);
    for (int i = 1; i <= n; i++) dis[i] = inf;
    dis[beg] = 0; 
    priority_queue<PII, vector<PII>, greater<PII> > q; q.push({0, beg});
    while (!q.empty()){
        PII t = q.top(); q.pop();
        int u = t.second;
        if (vis[u]) continue;
        vis[u] = 1;
        // for (auto &x : edge1[u])
        for (int i = head2[u]; i; i = g[i].nxt)
        {
            int v = g[i].to;
            if (vis[v]) continue;
            if (dis[v] > dis[u] + g[i].d){
                dis[v] = dis[u] + g[i].d;
                q.push({dis[v], v});
            }
        }
    }
    return 0;
}

struct node{
    int to;
    int f, g;
    node(){}
    node(int tt, int ff, int gg): to(tt), f(ff), g(gg){}
    bool operator < (const node &t) const{
        if(t.f == f) return t.g < g;
        return t.f < f;
    }
};

int astar(){
    priority_queue<node> q; q.push({s, dis[s], 0});
    int cnt = 0;
    if (s == e) k++;
    if (dis[s] == inf) return -1;
    while (!q.empty()){
        node t = q.top(); q.pop();
        if (t.to == e) cnt++;
        if (cnt == k) return t.g;
        // for (auto &x : edge[t.to])
        for (int i = head1[t.to]; i; i = f[i].nxt)
        {
            int v = f[i].to;
            q.push({v, t.g + f[i].d + dis[v], t.g + f[i].d});
        }
    }
    return -1;
}

int main(){
    while (~scanf("%d%d", &n, &m)){
        tot1 = tot2 = 0; ms(head1, 0); ms(head2, 0);
        while (m--){
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            // edge[u].emplace_back(v, w);
            add1(u, v, w);
            add2(v, u, w);
            // edge1[v].emplace_back(u, w);
        }
        scanf("%d%d%d", &s, &e, &k);
        dijkstra(e);
        int ans = astar();
        printf("%d\n", ans);
    }
    return 0;
}