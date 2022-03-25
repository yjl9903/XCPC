#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const ll inf = 1ll << 60;
const int mod = 998244353;
const int maxn = 1010 + 5;

bool vis[1 << 6][maxn];
struct node{
    int to; ll d;
    bool operator< (const node& b)const{
        return d > b.d;
    }
};

vector<PII> edge[maxn];
int n, m, p, a[maxn];
ll dp[1 << 6][maxn];

int main() {
    while (scanf("%d%d%d", &n, &m, &p) == 3) {
        ms(vis, 0);
        for (int i = 0; i <= n + m; i++) edge[i].clear();
        for (int i = 1; i <= n + m; i++) {
            scanf("%d", a + i);
            edge[0].push_back({i, a[i]});
            edge[i].push_back({0, a[i]});
        }
        for (int i = 1, u, v, w; i <= p; i++) {
            scanf("%d%d%d", &u, &v, &w);
            edge[u].push_back({v, w});
            edge[v].push_back({u, w});
        }
        int ss = 1 << (n + 1);
        for (int s = 1; s < ss; s++) for (int u = 0; u <= n + m; u++) dp[s][u] = inf;
        for (int u = 0; u <= n; u++) dp[1 << u][u] = 0;
        priority_queue<node> pq;
        for (int s = 1; s < ss; s++) {
            for (int u = 0; u <= n + m; u++) {
                for (int t = s; t; t = (t - 1) & s) {
                    dp[s][u] = min(dp[s][u], dp[t][u] + dp[s ^ t][u]);
                }
            }
            for (int u = 0; u <= n + m; u++) if (dp[s][u] != inf) pq.push({u, dp[s][u]});
            while (!pq.empty()) {
                node tp = pq.top(); pq.pop();
                if (vis[s][tp.to]) continue;
                vis[s][tp.to] = 1;
                for (auto& x: edge[tp.to]) {
                    if (dp[s][x.first] > dp[s][tp.to] + x.second) {
                        dp[s][x.first] = dp[s][tp.to] + x.second;
                        pq.push({x.first, dp[s][x.first]});
                    }
                }
            }
        }
        ll ans = inf;
        for (int i = 0; i <= n + m; i++) ans = min(ans, dp[ss - 1][i]);
        printf("%lld\n", ans);
    }
    return 0;
}