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
typedef pair<ll,ll> PII;
const int mod = 998244353;
const ll inf = 1ll << 60;
const int maxn = 30 + 5;

int n, m;
vector<PII> edge[maxn];

ll dis[maxn]; int vis[maxn];
ll cal(int no) {
    for (int i = 1; i <= n; i++) dis[i] = inf, vis[i] = 0;
    dis[1] = 0;
    priority_queue<PII> q; q.push({0, 1});
    while (!q.empty()) {
        PII tp = q.top(); q.pop();
        int u = tp.second;
        if (u == no) continue;
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto& x: edge[u]) {
            int v = x.first;
            if (v == no) continue;
            if (vis[v]) continue;
            if (dis[v] > dis[u] + x.second) {
                dis[v] = dis[u] + x.second;
                q.push({-dis[v], v});
            }
        }
    }
    return dis[n];
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        if (!n && !m) return 0;
        for (int i = 1, a, b, c; i <= m; i++) {
            scanf("%d%d%d", &a, &b, &c);
            edge[a].push_back({b, c});
            edge[b].push_back({a, c});
        }
        ll ans = cal(0);
        for (int i = 2; i < n; i++) {
            ll tot = cal(i);
            // cout << "tot: " << tot << endl;
            // if (tot == inf) continue;
            // ans = max(ans, tot);
            ans = max(ans, tot);
        }
        if (ans == inf) puts("Inf");
        else printf("%lld\n", ans);
        for (int i = 1; i <= n; i++) edge[i].clear();
    }
    return 0;
}