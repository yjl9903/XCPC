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

int n, m, s, e, k, t;
vector<PII> edge[maxn], edge1[maxn];

int vis[maxn], dis[maxn];
int dijkstra(int beg = 1){
    ms(vis, 0);
    for (int i = 1; i <= n; i++) dis[i] = inf;
    dis[beg] = 0; 
    priority_queue<PII, vector<PII>, greater<PII> > q; q.emplace(0, beg);
    while (!q.empty()){
        PII t = q.top(); q.pop();
        int u = t.second;
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto &x : edge1[u]){
            int v = x.first;
            if (vis[v]) continue;
            if (dis[v] > dis[u] + x.second){
                dis[v] = dis[u] + x.second;
                q.emplace(dis[v], v);
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
    priority_queue<node> q; q.emplace(s, dis[s], 0);
    int cnt = 0;
    if (dis[s] == inf) return inf;
    while (!q.empty()){
        node t = q.top(); q.pop();
        if (t.to == e) cnt++;
        if (cnt == k) return t.g;
        for (auto &x : edge[t.to]){
            q.emplace(x.first, t.g + x.second + dis[x.first], t.g + x.second);
        }
    }
    return inf;
}

int main(){
    while (~scanf("%d%d", &n, &m)){
        scanf("%d%d%d%d", &s, &e, &k, &t);
        for (int i = 0; i <= n; i++) edge[i].clear(), edge1[i].clear();
        while (m--){
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            edge[u].emplace_back(v, w);
            edge1[v].emplace_back(u, w);
        }
        dijkstra(e);
        int ans = astar();
        if (ans <= t) puts("yareyaredawa");
        else puts("Whitesnake!");
    }
    return 0;
}