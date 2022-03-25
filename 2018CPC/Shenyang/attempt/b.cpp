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
    ms(vis, 0); for (int i = 1; i <= n; i++) dis[i] = inf;
    dis[beg] = 0; 
    priority_queue<PII, vector<PII>, greater<PII> > q; q.push(make_pair(0, beg));
    while (!q.empty()){
        PII t = q.top(); q.pop();
        int u = t.second;
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = 0; i < edge[u].size(); i++){
            PII x = edge[u][i];
            int v = x.first;
            if (vis[v]) continue;
            if (dis[v] > dis[u] + x.second){
                dis[v] = dis[u] + x.second;
                q.push(make_pair(dis[v], v));
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
    priority_queue<node> q; q.push(node(s, dis[s], 0));
    int cnt = 0;
    if (s == e) k++;
    if (dis[s] == inf) return -1;
    while (!q.empty()){
        node t = q.top(); q.pop();
        if (t.to == e) cnt++;
        if (cnt == k) return t.g;
        for (int i = 0; i < edge[t.to].size(); i++){
            PII x = edge[t.to][i];
            q.push(node(x.first, t.g + x.second + dis[x.first], t.g + x.second));
        }
    }
    return -1;
}

int main(){
    while (~scanf("%d%d", &n, &m)){
        for (int i = 0; i <= n; i++) edge[i].clear(), edge1[i].clear();
        while (m--){
            int u, v, w; scanf("%d%d%d", &u, &v, &w);
            edge[u].push_back(make_pair(v, w));
            edge1[v].push_back(make_pair(u, w));
        }
        scanf("%d%d%d", &s, &e, &k);
        dijkstra(e);
        // for (int i = 1; i <= 2; i++) printf("%d\n", dis[i]);
        int ans = astar();
        printf("%d\n", ans);
    }
    return 0;
}