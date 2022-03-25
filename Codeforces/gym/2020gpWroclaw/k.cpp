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
#ifdef XLor
  #define dbg(args...) cout  << #args << " -> ", err(args)
  void err() { std::cout  << std::endl; }
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
const int inf = 1 << 28;
const int maxn = 1500 + 5;

int n, k, q, g[maxn][maxn], f[maxn][maxn];
int vis[maxn], pos[maxn], ans[maxn];
vector<int> line[maxn], bag[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
      bag[i].clear();
    }
    for (int i = 1; i <= n + k; i++) {
      for (int j = 1; j <= n + k; j++) {
        if (i == j) {
          g[i][j] = f[i][j] = 0;
        } else {
          g[i][j] = f[i][j] = inf;
        }
      }
    }
    for (int i = 1; i <= k; i++) {
      line[i].clear();
      vis[i] = false;
      int m, x;
      scanf("%d", &m);
      while (m--) {
        scanf("%d", &x);
        g[x][i + n] = g[i + n][x] = 0;
        line[i].push_back(x);
        bag[x].push_back(i);
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < bag[i].size(); j++) {
        for (int k = 0; k < j; k++) {
          int x = n + bag[i][j];
          int y = n + bag[i][k];
          g[x][y] = g[y][x] = min(g[x][y], 1);
        }
      }
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
      scanf("%d", pos + i);
      vis[pos[i]] = true;
    }
    auto trans = [&](int x) {
      dbg(x);
      x += n;
      for (int i = 1; i <= n + k; i++) {
        f[i][x] = f[x][i] = min(f[i][x], g[i][x]);
      }
      for (int i = 1; i <= n + k; i++) {
        for (int j = 1; j <= n + k; j++) {
          f[i][j] = min(f[i][j], f[i][x] + f[x][j]);
          // dbg(i, j, f[i][j]);
        }
      }
    };
    for (int i = 1; i <= k; i++) {
      if (!vis[i]) {
        trans(i);
      }
    }
    for (int i = q; i >= 0; i--) {
      int res = 0;
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
          if (f[i][j] < inf) {
            res = max(res, f[i][j]);
          }
        }
      }
      ans[i] = res;
      dbg(res);
      if (i > 0) {
        trans(pos[i]);
        vis[pos[i]] = false;
      }
    }
    for (int i = 0; i <= q; i++) {
      printf("%d\n", ans[i]);
    }
  }
  return 0;
}