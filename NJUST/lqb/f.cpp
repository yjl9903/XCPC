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
#include <map>
#include <set>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 20;
const int maxn = 1000 + 5;

int n, m, k, dis[maxn][maxn];
char s[maxn][maxn];

const vector<PII> dir = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

int main() {
  scanf("%d%d", &n, &m);
  queue<PII> q;
  for (int i = 1; i <= n; i++) {
    scanf("%s", s[i] + 1);
    for (int j = 1; j <= m; j++) {
      if (s[i][j] == 'g') {
        q.emplace(i, j);
      } else {
        dis[i][j] = inf;
      }
    }
  }
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    for (auto d: dir) {
      int x = u.first + d.first;
      int y = u.second + d.second;
      if (x < 1 || x > n || y < 1 || y > m) continue;
      if (dis[x][y] > dis[u.first][u.second] + 1) {
        dis[x][y] = dis[u.first][u.second] + 1;
        q.emplace(x, y);
      }
    }
  }
  scanf("%d", &k);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      putchar(dis[i][j] <= k ? 'g' : '.');
    }
    puts("");
  }
  return 0;
}