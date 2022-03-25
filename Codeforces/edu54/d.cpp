#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 300000 + 5;

struct node{
    int to, id; ll d;
    node(int a, ll b, int c):to(a), d(b), id(c){}
    bool operator<(const node& b)const{
        return d > b.d;
    }
};
vector<node> edge[maxn];
int n, m, k;

bool vis[maxn]; ll dis[maxn];
void dijkstra(){
    for (int i = 2; i <= n; i++) dis[i] = 1ll << 60;
    dis[1] = 0; 
    priority_queue<node> q;
    q.emplace(1, 0, 0);
    while (!q.empty()){
        node t = q.top(); q.pop();
        if (vis[t.to]) continue;
        vis[t.to] = 1;
        for (auto& x : edge[t.to]){
            int v = x.to;
            if (vis[v]) continue;
            if (dis[v] > dis[t.to] + x.d){
                dis[v] = dis[t.to] + x.d;
                q.emplace(v, dis[v], 0);
            }
        }
    }
}

vector<int> ans;
void dfs(int u){
    for (auto& x : edge[u]){
        if (dis[u] + x.d == dis[x.to] && !vis[x.to]){
            vis[x.to] = 1;
            ans.push_back(x.id);
            dfs(x.to);
        }
    }
}

int main(){
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1, x, y, w; i <= m; i++){
        scanf("%d%d%d", &x, &y, &w);
        edge[x].emplace_back(y, w, i);
        edge[y].emplace_back(x, w, i);
    }
    dijkstra(); 
    ms(vis, 0); dfs(1);
    printf("%d\n", min(k, (int)ans.size()));
    for (int i = 0; i < min(k, (int)ans.size()); i++) printf("%d ", ans[i]);
    return 0;
}