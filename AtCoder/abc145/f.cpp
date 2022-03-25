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
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300 + 5;

int n, k, h[maxn];
ll dp[maxn][maxn];

int main() {
  scanf("%d%d", &n, &k);
  if (n == k) return puts("0"), 0;
  for (int i = 1; i <= n; i++) scanf("%d", h + i);
  for (int i = 1; i <= n; i++) {
    dp[i][1] = h[i];
    // dbg(i, 1, dp[i][1]);
    for (int j = 2; j <= n - k; j++) {
      dp[i][j] = 1ll << 61;
      for (int k = j - 1; k < i; k++) {
        dp[i][j] = min(dp[i][j], dp[k][j - 1] + max(h[i] - h[k], 0));
      }
      // dbg(i, j, dp[i][j]);
    }
  }
  ll ans = 1ll << 61;
  for (int i = 1; i <= n; i++) {
    ans = min(ans, dp[i][n - k]);
  }
  cout << ans;
  return 0;
}