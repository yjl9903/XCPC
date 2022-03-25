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
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
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
const int maxn = 1000000 + 5;

int n, r1, r2, r3, d, a[maxn];
ll dp[maxn][2];

int main() {
  scanf("%d%d%d%d%d", &n, &r1, &r2, &r3, &d);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  dp[1][0] = 1ll * a[1] * r1 + r3;
  dp[1][1] = min(1ll * (a[1] + 1) * r1, 1ll * r2);
  for (int i = 2; i <= n; i++) {
    ll cost = min(1ll * (a[i] + 1) * r1, 1ll * r2);

    dp[i][0] = dp[i - 1][0] + d + (1ll * a[i] * r1 + r3);
    dp[i][0] = min(dp[i][0], dp[i - 1][1] + d + cost + d + r1 + d + r1);
    dp[i][0] = min(dp[i][0], dp[i - 1][1] + d + (1ll * a[i] * r1 + r3) + d + d + r1);

    dp[i][1] = min(dp[i - 1][0] + d + cost, dp[i - 1][1] + d + cost + d + r1 + d);
  }
  ll ans = dp[n][0];
  if (n > 1) {
    ans = min(ans, dp[n - 1][1] + d + 1ll * r1 * a[n] + r3 + d + r1);
  }
  printf("%lld\n", ans);
  return 0;
}