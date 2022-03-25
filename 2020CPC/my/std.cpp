#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int N = 1e5 + 10;
const int S = 51;
int dis[N][S];
int f[N];
int du[N];
int mn[N];
vector<int> gin[N], g[N];
int n, m, T, k;
vector<pair<int, int> > d[2];
int main() {
  scanf("%d", &T);
  int id = 0;
  while (T--) {
    printf("Case #%d:\n", ++id);
    scanf("%d %d %d", &n, &m, &k);
    memset(dis, 0, sizeof(dis));
    memset(f, 0, sizeof(f));
    memset(du, 0, sizeof(du));
    for (int i = 1; i <= m; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      gin[y].push_back(x);
      g[x].push_back(y);
      g[y].push_back(x);
      du[x]++;
    }
    for (int i = 1; i <= n; i++) mn[i] = 1e9;
    dis[n][0] = 1;
    mn[n] = 0;
    f[n] = 0;
    d[0].push_back({n, 0});
    bool bz = 0;
    while (d[bz].size()) {
      for (int i = 0; i < d[bz].size(); i++) {
        auto v = d[bz][i];
        if (v.second != k) {
          for (auto u : g[v.first])
            if (!dis[u][v.second + 1] && mn[u] > v.second + 1) {
              dis[u][mn[u] = v.second + 1] = dis[v.first][v.second] + 1;
							d[bz ^ 1].push_back({u, v.second + 1});
            }
        }
        if (!f[v.first]) {
          f[v.first] = dis[v.first][v.second];
          for (auto u : gin[v.first])
            if (!(--du[u])) {
              mn[u] = 0;
              dis[u][0] = f[v.first] + 1;
              d[bz ^ 1].push_back({u, 0});
            }
          if (!du[v.first] && !dis[v.first][0]) {
            dis[v.first][0] = dis[v.first][v.second] + 1;
            mn[v.first] = 0;
            d[bz ^ 1].push_back({v.first, 0});
          }
        }
      }
      d[bz].clear();
      bz ^= 1;
    }
    for (int i = 1; i <= n; i++) printf("%d\n", f[i] - 1);
    for (int i = 1; i <= n; i++) gin[i].clear(), g[i].clear();
  }
  return 0;
}
