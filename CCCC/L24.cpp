#include <bits/stdc++.h>
using namespace std;
using PII = pair<int,int>;
const int maxn = 100000 + 5;

int n, m;
map<int,int> edge[maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    if (edge[u].count(v)) {
      edge[u][v] = min(edge[u][v], w);
    } else {
      edge[u][v] = w;
    }
    if (edge[v].count(u)) {
      edge[v][u] = min(edge[v][u], w);
    } else {
      edge[v][u] = w;
    }
  }
  int q, ans = 0, mn = -1, pos;
  scanf("%d", &q);
  for (int cas = 1; cas <= q; cas++) {
    int k;
    scanf("%d", &k);
    vector<int> path;
    for (int i = 1; i <= k; i++) {
      int x;
      scanf("%d", &x);
      path.push_back(x);
    }
    if (path.size() == n) {
      if (edge[0].count(path[0]) && edge[path.back()].count(0)) {
        int cur = edge[0][path[0]] + edge[path.back()][0];
        bool flag = true;
        set<int> vis = { path[0] };
        for (int i = 1; i < path.size(); i++) {
          vis.insert(path[i]);
          int u = path[i - 1], v = path[i];
          if (edge[u].count(v)) {
            cur += edge[u][v];
          } else {
            flag = false;
            break;
          }
        }
        if (flag && vis.size() == n) {
          ans++;
          if (mn == -1 || cur < mn) {
            mn = cur;
            pos = cas;
          }
        }
      }
    }
  }
  printf("%d\n%d %d\n", ans, pos, mn);
  return 0;
}