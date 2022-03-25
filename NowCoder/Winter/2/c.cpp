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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
  return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}
inline int inv(int x) {
  return qpow(x, mod - 2);
}

int n, p[maxn], dp[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", p + i);
  }
  dp[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = i; j >= 1; j--) {
      int sum = mul(dp[j], sub(1, p[i]));
      sum = add(sum, mul(dp[j - 1], p[i]));
      dp[j] = sum;
    }
  }
  int dp0 = 1;
  for (int i = 1; i <= n; i++) {
    dp0 = sub(dp0, dp[i]);
  }
  printf("%d", dp0);
  for (int i = 1; i <= n; i++) {
    printf(" %d", dp[i]);
  }
  return 0;
}