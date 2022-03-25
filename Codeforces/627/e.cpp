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
const int maxn = 3000 + 5;

int n, h, l, r, a[maxn], dp[maxn][maxn];

int main() {
  scanf("%d%d%d%d", &n, &h, &l, &r);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    // if (i == 1) continue;
    for (int j = 0; j < h; j++) {
      dp[i][j] = -inf;
    }
  }
  dp[1][0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < h; j++) {
      if (dp[i][j] == -inf) continue;
      int nx = (j + a[i]) % h;
      dp[i + 1][nx] = max(dp[i + 1][nx], dp[i][j] + int(l <= nx && nx <= r));
      nx = (j + a[i] - 1) % h;
      dp[i + 1][nx] = max(dp[i + 1][nx], dp[i][j] + int(l <= nx && nx <= r));
      dbg(i, j, dp[i][j]);
    }
  }
  int ans = 0;
  for (int i = 0; i < h; i++) ans = max(ans, dp[n + 1][i]);
  printf("%d\n", ans);
  return 0;
}