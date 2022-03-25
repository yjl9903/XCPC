#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const int inf = 1 << 30;

int n, w[maxn], dis[maxn], vis[maxn];

struct node{
    int u, d;
    bool operator < (const node& b) const {
        return  d > b.d;
    }
};

int dijkstra(){
    ms(vis, 0); fill(dis, dis + maxn, inf);
    priority_queue<node> q;
    q.push({1, 0}); dis[1] = 0;
    while (!q.empty()){
        node t = q.top(); q.pop();
        int u = t.u;
        if (vis[u]) continue;
        vis[u] = 1;
        for (int i = 1; i <= n; i++) {
            int d = sqrt(1.0 * abs(w[u] - w[i]));
            if (dis[i] > dis[u] + d){
                dis[i] = dis[u] + d;
                q.push({i, dis[i]});
            }
        }
    }
    return dis[n];
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
        // printf("%d\n", dijkstra());
        int res = sqrt(1.0 * abs(w[n] - w[1]));
        printf("%d\n", res);
    }
    return 0;
} 