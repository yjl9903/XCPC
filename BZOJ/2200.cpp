#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 25000 + 5;

int n, r, p, s, pre[maxn];
int vis[maxn], dis[maxn], deg[maxn];
vector<PII> edge[maxn];
vector<int> block[maxn];

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}

int main() {
  scanf("%d%d%d%d", &n, &r, &p, &s);
  for (int i = 1; i <= n; i++) pre[i] = i, dis[i] = inf;
  for (int i = 1, u, v, w; i <= r; i++) {
    scanf("%d%d%d", &u, &v, &w);
    pre[find(u)] = find(v);
    edge[u].push_back({v, w});
    edge[v].push_back({u, w});
  }
  for (int i = 1; i <= n; i++) block[find(i)].push_back(i);
  for (int i = 1, u, v, w; i <= p; i++) {
    scanf("%d%d%d", &u, &v, &w);
    edge[u].push_back({v, w});
    if (find(u) != find(v)) {
      deg[find(v)]++;
    }
  }
  dis[s] = 0;
  queue<int> q;
  for (int i = 1; i <= n; i++) { 
    if (find(i) == i && !deg[i]) q.push(i);
  }
  while (!q.empty()) {
    int rt = q.front(); q.pop();
    priority_queue<PII> pq;
    for (int x: block[rt]) pq.emplace(-dis[x], x);
    while (!pq.empty()) {
      int u = pq.top().second; pq.pop();
      if (vis[u]) continue;
      vis[u] = 1;
      for (auto x: edge[u]) {
        int v = x.first, w = x.second;
        if (dis[u] != inf && dis[v] > dis[u] + w) {
          dis[v] = dis[u] + w;
          if (find(u) == find(v)) pq.emplace(-dis[v], v);
        }
        if (find(u) != find(v)) {
          deg[find(v)]--;
          if (deg[find(v)] == 0) {
            q.push(find(v));
          }
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    if (dis[i] == inf) puts("NO PATH");
    else printf("%d\n", dis[i]);
  }
  return 0;
}