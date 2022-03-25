#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 20;
const int maxn = 1000 + 5;

const vector<PII> dir = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

int n, m, k, q, a[maxn][maxn];
int dis[41][maxn][maxn], cdis[41][41];
vector<PII> pos[41];

void get(int col, int dis[maxn][maxn]) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dis[i][j] = inf;
    }
  }
  queue<PII> q;
  for (auto& x: pos[col]) {
    dis[x.first][x.second] = 0;
    q.emplace(x.first, x.second);
  }
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    if (u.second == -1) {
      for (auto& x: pos[u.first]) {
        if (cdis[col][u.first] + 1 < dis[x.first][x.second]) {
          dis[x.first][x.second] = cdis[col][u.first] + 1;
          q.emplace(x.first, x.second);
        }
      }
    } else {
      for (auto& d: dir) {
        int x = u.first + d.first, y = u.second + d.second;
        if (x < 1 || y < 1 || x > n || y > m) continue;
        if (dis[u.first][u.second] + 1 < dis[x][y]) {
          dis[x][y] = dis[u.first][u.second] + 1;
          q.emplace(x, y);
        }
        if (dis[u.first][u.second] + 1 < cdis[col][a[x][y]]) {
          cdis[col][a[x][y]] = dis[u.first][u.second] + 1;
          q.emplace(a[x][y], -1);
        }
      }
    }
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%d", &a[i][j]);
      pos[a[i][j]].emplace_back(i, j);
    }
  }
  for (int i = 1; i <= k; i++) {
    for (int j = 1; j <= k; j++) {
      if (i == j) continue;
      cdis[i][j] = inf;
    }
  }
  for (int c = 1; c <= k; c++) {
    get(c, dis[c]);
  }
  scanf("%d", &q);
  while (q--) {
    int r1, c1, r2, c2;
    scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
    int ans = abs(r2 - r1) + abs(c2 - c1);
    for (int i = 1; i <= k; i++) {
      ans = min(ans, dis[i][r1][c1] + dis[i][r2][c2] + 1);
    }
    printf("%d\n", ans);
  }
  return 0;
}