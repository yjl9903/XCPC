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
#ifdef XLor
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, m, k;
vector<int> edge[maxn], G[maxn];
int f[maxn], dis[maxn][55], deg[maxn];

struct Node {
  int u, k, d;
};

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
      G[i].clear();
      deg[i] = 0;
    }
    for (int i = 1; i <= m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      edge[u].push_back(v);
      edge[v].push_back(u);
      G[v].push_back(u);
      deg[u]++;
    }
    for (int i = 1; i <= n; i++) {
      if (deg[i] == 0) {
        G[i].push_back(i);
        deg[i]++;
      }
      f[i] = -1;
      for (int j = 0; j <= k; j++) {
        dis[i][j] = -1;
      }
    }
    queue<Node> q;
    dis[n][0] = 0;
    q.push({ n, 0, 0 });
    while (!q.empty()) {
      int u = q.front().u;
      int uk = q.front().k;
      q.pop();

      if (uk < k) {
        for (int v: edge[u]) {
          if (dis[v][uk + 1] == -1) {
            dis[v][uk + 1] = dis[u][uk] + 1;
            q.push({ v, uk + 1, dis[v][uk + 1] });
          }
        }
      }

      if (f[u] == -1) {
        f[u] = dis[u][uk];
        for (int v: G[u]) {
          deg[v]--;
          if (deg[v] == 0) {
            dis[v][0] = f[u] + 1;
            q.push({ v, 0, dis[v][0] });
          }
        }
      }
    }
    printf("Case #%d:\n", ++kase);
    for (int i = 1; i <= n; i++) {
      printf("%d\n", f[i]);
    }
  }
  return 0;
}