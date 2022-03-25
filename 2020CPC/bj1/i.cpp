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
const int inf = 1 << 30;
const int maxn = 1000 + 5;

const vector<PII> dir = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

int n, m, vis[maxn][maxn];
char mp[maxn][maxn];

PII run(char c, int x, int y) {
  if (c == 'W') {
    return { x - 1, y };
  } else if (c == 'A') {
    return { x, y - 1 };
  } else if (c == 'S') {
    return { x + 1, y };
  } else if (c == 'D') {
    return { x, y + 1 };
  } else {
    assert(false);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%s", mp[i] + 1);
  }
  queue<PII> q;
  for (int i = 1; i <= n; i++) {
    if (mp[i][1] == 'A') {
      q.emplace(i, 1);
      vis[i][1] = true;
    }
    if (mp[i][m] == 'D') {
      q.emplace(i, m);
      vis[i][m] = true;
    }
  }
  for (int j = 1; j <= m; j++) {
    if (mp[1][j] == 'W') {
      q.emplace(1, j);
      vis[1][j] = true;
    }
    if (mp[n][j] == 'S') {
      q.emplace(n, j);
      vis[n][j] = true;
    }
  }
  while (!q.empty()) {
    auto u = q.front();
    q.pop();
    for (auto d: dir) {
      int x = u.first + d.first;
      int y = u.second + d.second;
      if (x < 1 || x > n || y < 1 || y > m) continue;
      auto tmp = run(mp[x][y], x, y);
      if (u == tmp) {
        vis[x][y] = true;
        q.emplace(x, y);
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      ans += vis[i][j];
    }
  }
  printf("%d\n", ans);
  return 0;
}