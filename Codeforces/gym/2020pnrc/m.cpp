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
const int inf = 1 << 30;
const int maxn = 1000 + 5;

char mp[maxn][maxn];
int n, m, vis[maxn][maxn];

const vector<PII> dir = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
const vector<PII> dirL = {
  {1, 1}, {-1, -1}
};
const vector<PII> dirR = {
  {-1, 1}, {1, -1}
};

int bfs(int x, int y) {
  if (mp[x][y] != '.') return false;
  if (vis[x][y]) return false;
  queue<PII> q;
  vis[x][y] = true;
  q.emplace(x, y);
  while (!q.empty()) {
    auto u = q.front();
    q.pop();
    for (auto d: dir) {
      int x = u.first + d.first;
      int y = u.second + d.second;
      if (x < 1 || x > n || y < 1 || y > m) continue;
      if (vis[x][y]) continue;
      if (mp[x][y] != '.') continue;
      vis[x][y] = true;
      q.emplace(x, y);
    }
    for (auto d: dirL) {
      int x = u.first + d.first;
      int y = u.second + d.second;
      if (x < 1 || x > n || y < 1 || y > m) continue;
      if (vis[x][y]) continue;
      if (mp[x][y] != '.') continue;
      if (mp[u.first][y] == '\\' && mp[x][u.second] == '\\') {
        vis[x][y] = true;
        q.emplace(x, y);
      }
    }
    for (auto d: dirR) {
      int x = u.first + d.first;
      int y = u.second + d.second;
      if (x < 1 || x > n || y < 1 || y > m) continue;
      if (vis[x][y]) continue;
      if (mp[x][y] != '.') continue;
      if (mp[u.first][y] == '/' && mp[x][u.second] == '/') {
        vis[x][y] = true;
        q.emplace(x, y);
      }
    }
  }
  return true;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%s", mp[i] + 1);
  }
  int ans = 0;
  for (int i = 1; i < n; i++) {
    for (int j = 1; j < m; j++) {
      if (mp[i][j] == '/' && mp[i][j + 1] == '\\' && mp[i + 1][j] == '\\' && mp[i + 1][j + 1] == '/') {
        ans++;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    bfs(i, 1);
    bfs(i, m);
  }
  for (int i = 1; i <= m; i++) {
    bfs(1, i);
    bfs(n, i);
  }
  for (int i = 2; i < n; i++) {
    for (int j = 2; j < m; j++) {
      ans += bfs(i, j);
    }
  }
  printf("%d\n", ans);
  return 0;
}