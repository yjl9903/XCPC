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
const int maxn = 200 + 5;

const vector<PII> dir { {1, 0}, {0, -1}, {-1, 0}, {0, 1},   };

int n, m, pre[maxn][maxn], bel[maxn][maxn], col[maxn][maxn], val[maxn][maxn];
char s[maxn][maxn];

void path(int sx, int sy, int val) {
  bel[sx][sy] |= val;
  queue<PII> q;
  q.emplace(sx, sy);
  while (!q.empty()) {
    auto u = q.front();
    q.pop();
    vector<tuple<int,int,int> > nxt;
    for (int i = 0; i < 4; i++) {
      int x = u.first + dir[i].first;
      int y = u.second + dir[i].second;
      if (bel[x][y] & val) continue;
      if (s[x][y] != 'X') continue;
      nxt.emplace_back(x, y, i);
    }
    if (u.first == sx && u.second == sy) {
      assert(nxt.size() == 2);
      for (auto& p: nxt) {
        int x = get<0>(p);
        int y = get<1>(p);
        int d = get<2>(p);
        bel[x][y] |= val;
        pre[x][y] = d;
        q.emplace(x, y);
      }
    } else if (!nxt.empty()) {
      if (nxt.size() == 1) {
        int x = get<0>(nxt[0]);
        int y = get<1>(nxt[0]);
        int d = get<2>(nxt[0]);
        bel[x][y] |= val;
        pre[x][y] = d;
        q.emplace(x, y);
      } else {
        for (auto& p: nxt) {
          int x = get<0>(p);
          int y = get<1>(p);
          int d = get<2>(p);
          if (d == pre[u.first][u.second]) {
            bel[x][y] |= val;
            pre[x][y] = d;
            q.emplace(x, y);
          }
        }
      }
    }
  }
}

void color(int sx, int sy) {
  if (col[sx][sy]) return ;
  if (s[sx][sy] != '.') return ;
  col[sx][sy] = true;
  queue<PII> q;
  q.emplace(sx, sy);
  while (!q.empty()) {
    auto u = q.front();
    q.pop();
    for (auto& d: dir) {
      int x = u.first + d.first;
      int y = u.second + d.second;
      if (!col[x][y] && s[x][y] == '.') {
        col[x][y] = true;
        q.emplace(x, y);
      }
    }
  }
}

void extend(int sx, int sy, int vv) {
  if (val[sx][sy] & vv) return ;
  val[sx][sy] |= vv;
  queue<PII> q;
  q.emplace(sx, sy);
  while (!q.empty()) {
    auto u = q.front();
    q.pop();
    for (auto& d: dir) {
      int x = u.first + d.first;
      int y = u.second + d.second;
      if (col[x][y]) continue;
      if (val[x][y] & vv) continue;
      if (s[x][y] == '.') {
        val[x][y] |= vv;
        q.emplace(x, y);
      }
    }
  }
}

bool vis1[maxn][maxn], vis2[maxn][maxn];
int rtx, rty, dirRes = -1;
void dfs1(int ux, int uy, int vv) {
  vis1[ux][uy] = true;
  for (int i = 0; i < 4; i++) {
    int x = ux + dir[i].first;
    int y = uy + dir[i].second;
    if (x == rtx && y == rty) continue;
    if (bel[x][y] & vv) {
      if (vis1[x][y]) continue;
      dfs1(x, y, vv);
      {
        int xx = ux + dir[(i + 1) % 4].first;
        int yy = uy + dir[(i + 1) % 4].second;
        if (val[xx][yy] == vv) {
          if (dirRes == -1) {
            dirRes = 1;
          } else {
            assert(dirRes == 1);
          }
        }
      }
      {
        int xx = ux + dir[(i + 3) % 4].first;
        int yy = uy + dir[(i + 3) % 4].second;
        if (val[xx][yy] == vv) {
          if (dirRes == -1) {
            dirRes = 3;
          } else {
            assert(dirRes == 3);
          }
        }
      }
    }
  }
}
void dfs2(int ux, int uy, int vv) {
  vis2[ux][uy] = true;
  for (int i = 0; i < 4; i++) {
    int x = ux + dir[i].first;
    int y = uy + dir[i].second;
    if (x == rtx && y == rty) continue;
    if (bel[x][y] & vv) {
      if (vis2[x][y]) continue;
      dfs2(x, y, vv);
      {
        int xx = ux + dir[(i + dirRes) % 4].first;
        int yy = uy + dir[(i + dirRes) % 4].second;
        if (s[xx][yy] == '.' && !col[xx][yy]) {
          extend(xx, yy, 3);
        }
      }
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s[i] + 1);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (s[i][j] == 'A') {
        path(i, j, 1);
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (s[i][j] == 'B') {
        path(i, j, 2);
      }
    }
  }
  // for (int i = 1; i <= n; i++) {
  //   for (int j = 1; j <= m; j++) {
  //     cout << bel[i][j] << ' ';
  //   }
  //   cout << endl;
  // }
  for (int i = 1; i <= n; i++) {
    color(i, 1);
    color(i, m);
  }
  for (int j = 1; j <= m; j++) {
    color(1, j);
    color(n, j);
  }

  int ans[4] = { 0, 0, 0, 0 };
  int caled = false;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (bel[i][j] == 1 && !caled) {
        if (s[i + 1][j] == '.' && !col[i + 1][j]) {
          extend(i + 1, j, 1);
          caled = 1;
          break;
        }
      } else if (bel[i][j] == 2 && !caled) {
        if (s[i + 1][j] == '.' && !col[i + 1][j]) {
          extend(i + 1, j, 2);
          caled = 2;
          break;
        }
      }
    }
    if (caled) break;
  }
  assert(caled);
  
  for (int i = 1; i <= n; i++) {
    bool ok = false;
    for (int j = 1; j <= m; j++) {
      if (bel[i][j] == caled) {
        ok = true;
        rtx = i;
        rty = j;
        dfs1(i, j, caled);
        assert(dirRes != -1);
        dfs2(i, j, caled);
        break;
      }
    }
    if (ok) break;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (s[i][j] == '.' && !col[i][j] && !val[i][j]) {
        extend(i, j, 3 ^ caled);
      }
    }
  }

  // for (int i = 1; i <= n; i++) {
  //   for (int j = 1; j <= m; j++) {
  //     cout << val[i][j] << ' ';
  //   }
  //   cout << endl;
  // }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      ans[val[i][j]]++;
    }
  }
  printf("%d %d %d\n", ans[1], ans[2], ans[3]);
  return 0;
}