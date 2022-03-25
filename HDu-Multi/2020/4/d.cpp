#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const ll inf = 1ll << 60;
const int maxn = 200000 + 5;

int n, m, s, t, X;
char tp[maxn];
vector<PII> edge[maxn];
ll dis[maxn][2];
bool vis[maxn][2];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d%d%s", &n, &m, &s, &t, &X, tp + 1);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
    }
    for (int i = 1, u, v, w; i <= m; i++) {
      scanf("%d%d%d", &u, &v, &w);
      edge[u].emplace_back(v, w);
      edge[v].emplace_back(u, w);
    }

    for (int i = 1; i <= n; i++) {
      dis[i][0] = dis[i][1] = inf;
      vis[i][0] = vis[i][1] = false;
    }
    priority_queue< pair<ll,int> > pq;
    if (tp[s] == 'L') {
      dis[s][0] = 0;
      pq.emplace(0ll, s);
    } else if (tp[s] == 'R') {
      dis[s][1] = 0;
      pq.emplace(0ll, s + n);
    } else {
      dis[s][0] = 0;
      dis[s][1] = 0;
      pq.emplace(0ll, s);
      pq.emplace(0ll, s + n);
    }

    while (!pq.empty()) {
      auto tot = pq.top(); pq.pop();
      int u = tot.second > n ? tot.second - n : tot.second;
      int k = tot.second > n ? 1 : 0;
      if (vis[u][k]) continue;
      vis[u][k] = true;
      for (auto& x: edge[u]) {
        int v = x.first;
        int w = x.second;
        if (tp[v] == 'L') {
          ll d = dis[u][k] + w + (k == 0 ? 0 : X);
          if (d < dis[v][0]) {
            dis[v][0] = d;
            pq.emplace(-d, v);
          }
        } else if (tp[v] == 'R') {
          ll d = dis[u][k] + w + (k == 1 ? 0 : X);
          if (d < dis[v][1]) {
            dis[v][1] = d;
            pq.emplace(-d, v + n);
          }
        } else {
          {
            ll d = dis[u][k] + w + (k == 0 ? 0 : X);
            if (d < dis[v][0]) {
              dis[v][0] = d;
              pq.emplace(-d, v);
            }
          }
          {
            ll d = dis[u][k] + w + (k == 1 ? 0 : X);
            if (d < dis[v][1]) {
              dis[v][1] = d;
              pq.emplace(-d, v + n);
            }
          }
        }
      }
    }

    if (tp[t] == 'L') {
      printf("%lld\n", dis[t][0]);
    } else if (tp[t] == 'R') {
      printf("%lld\n", dis[t][1]);
    } else {
      printf("%lld\n", min(dis[t][0], dis[t][1]));
    }
  }
  return 0;
}