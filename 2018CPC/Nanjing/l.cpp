#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

struct edge{int to, nxt, d;}f[maxn * 2];
int head[maxn], tot;
void add(int x, int y, int d){
    f[++tot] = {y, head[x], d};
    head[x] = tot;
}

int n, m, k;

bool vis[11][maxn];
ll dis[11][maxn];
struct node{
    int to, k; 
    ll d;
    bool operator< (const node& b)const{
        return d > b.d;
    }
};

ll dijkstra(){
    ms(vis, 0);
    for (int j = 0; j <= k; j++){
        dis[j][1] = 0;
        for (int i = 2; i <= n; i++) 
            dis[j][i] = 1ll << 60;
    }
    priority_queue<node> q;
    q.push({1, 0, 0}); 
    while (!q.empty()){
        node t = q.top(); q.pop();
        if (vis[t.k][t.to]) continue;
        // printf("+ %d: %d %lld\n", t.to, t.k, t.d);
        // if (t.to == n) return dis[t.d];
        vis[t.k][t.to] = 1;
        for (int i = head[t.to]; i; i = f[i].nxt){
            int v = f[i].to;
            if (vis[t.k][v]) continue;
            if (dis[t.k][v] > dis[t.k][t.to] + 1ll * f[i].d){
                dis[t.k][v] = dis[t.k][t.to] + 1ll * f[i].d;
                q.push({v, t.k, dis[t.k][v]});
            }
            if (t.k < k && dis[t.k + 1][v] > dis[t.k][t.to]){
                dis[t.k + 1][v] = dis[t.k][t.to];
                // printf("- %d: %d %lld\n", v, t.k + 1, dis[t.k + 1][v]);
                q.push({v, t.k + 1, dis[t.k + 1][v]});
            }
        }
    }
    ll ans = 1ll << 60;
    for (int i = 0; i <= k; i++){
        ans = min(ans, dis[i][n]);
    }
    return ans;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        ms(head, 0); tot = 0;
        scanf("%d%d%d", &n, &m, &k);
        int x, y, d;
        while (m--){
            scanf("%d%d%d", &x, &y, &d);
            add(x, y, d);
        }
        printf("%lld\n", dijkstra());
    }
    return 0;
}