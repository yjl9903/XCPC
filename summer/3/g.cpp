#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
// typedef pair<ll,int> PLI;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 4000 + 5;

map<PII,int> mp;
int n, m, uu[maxn * 2], vv[maxn * 2], ww[maxn * 2];
vector<PII> edge[maxn * 2];

int vis[maxn * 2], dis[maxn * 2], ans;
int dijkstra(int s, int t, int w) {
    priority_queue<PII> pq; pq.push({0, s});
    for (int i = 1; i <= n; i++) dis[i] = inf, vis[i] = 0;
    dis[s] = 0;
    while (!pq.empty()) {
        PII tp = pq.top(); pq.pop(); int u = tp.second;
        if (vis[u]) continue;
        if (u == t) return dis[t];
        vis[u] = 1;
        if (w + dis[u] > ans) return inf;
        for (auto& x: edge[u]) {
            int v = x.first;
            if (vis[v]) continue;
            if (dis[v] > dis[u] + x.second) {
                dis[v] = dis[u] + x.second;
                pq.push({-dis[v], v});
            }
        }
    }
    return dis[t];
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d", &m);
        n = 0; mp.clear();
        auto gid = [&](int x, int y)-> int {
            if (mp.count({x, y})) return mp[{x, y}];
            return mp[{x, y}] = ++n;
        };
        for (int i = 1; i <= m; i++) {
            int x1, x2, y1, y2, w;
            scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &w);
            int u = gid(x1, y1), v = gid(x2, y2);
            uu[i] = u; vv[i] = v; ww[i] = w;
            edge[u].push_back({v, w}); edge[v].push_back({u, w});
        }
        ans = inf;
        for (int i = 1; i <= m; i++) {
            for (int j = 0; j < (int)edge[uu[i]].size(); j++) {
                if (edge[uu[i]][j].first == vv[i] && edge[uu[i]][j].second == ww[i]) {
                    swap(edge[uu[i]][j], edge[uu[i]][(int)edge[uu[i]].size() - 1]);
                    edge[uu[i]].pop_back(); break;
                }
            }
            for (int j = 0; j < (int)edge[vv[i]].size(); j++) {
                if (edge[vv[i]][j].first == uu[i] && edge[vv[i]][j].second == ww[i]) {
                    swap(edge[vv[i]][j], edge[vv[i]][(int)edge[vv[i]].size() - 1]);
                    edge[vv[i]].pop_back(); break;
                }
            }
            ans = min(ans, ww[i] + dijkstra(uu[i], vv[i], ww[i]));
            edge[uu[i]].push_back({vv[i], ww[i]});
            edge[vv[i]].push_back({uu[i], ww[i]});
        }
        printf("Case #%d: ", ++kase);
        if (ans == inf) puts("0");
        else printf("%d\n", ans);
        for (int i = 1; i <= n; i++) edge[i].clear();
    }
    return 0;
}