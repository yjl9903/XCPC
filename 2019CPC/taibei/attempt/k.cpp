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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const ll inf = 1ll << 60;
const int maxn = 1000 + 5;

int n, a[maxn], pre[maxn];
ll dp[maxn][maxn];

ll solve(int l, int r) {
  if (l >= r) {
    return 0;
  }
  if (dp[l][r] != -1) {
    return dp[l][r];
  }
  ll ans = inf;
  for (int k = l; k < r; k++) {
    ans = min(ans, solve(l, k) + solve(k + 1, r));
  }
  return dp[l][r] = ans + pre[r] - pre[l - 1];
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      pre[i] = pre[i - 1] + a[i];
      for (int j = 1; j <= n; j++) {
        dp[i][j] = -1;
      }
    }
    printf("%lld\n", solve(1, n));
  }
  return 0;
}