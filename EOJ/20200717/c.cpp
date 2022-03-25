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
const int maxn = 4000 + 5;

int n, m, a, b, pre[maxn][maxn];
int ans[maxn][maxn];

int main() {
  scanf("%d%d%d%d", &n, &m, &a, &b);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int x; scanf("%d", &x);
      pre[i][j] = x;
      pre[i][j] += pre[i - 1][j];
      pre[i][j] += pre[i][j - 1];
      pre[i][j] -= pre[i - 1][j - 1];
      dbg(i, j, pre[i][j]);
    }
  }
  auto query = [&](int x1, int y1, int x2, int y2) {
    return pre[x2][y2] + pre[x1 - 1][y1 - 1] - pre[x2][y1 - 1] - pre[x1 - 1][y2];
  };
  int mx = 0;
  for (int i = 1; i <= a; i++) {
    for (int j = 1; j <= b; j++) {
      int x1 = n - (min(i + n - 1, a) - i + 1) + 1, x2 = min(i, n);
      int y1 = m - (min(j + m - 1, b) - j + 1) + 1, y2 = min(j, m);
      // dbg(i, j);
      // dbg(x1, y1, x2, y2);
      ans[i][j] = query(x1, y1, x2, y2);
      mx = max(mx, ans[i][j]);
      // dbg(i, j, ans[i][j]);
    }
  }
  for (int i = 1; i <= a; i++) {
    for (int j = 1; j <= b; j++) {
      int r = 100.0 * ans[i][j] / mx;
      printf("%d%c", r, " \n"[j == b]);
    }
  }
  return 0;
}