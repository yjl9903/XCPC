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
const int maxn = 3000 + 5;

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

char s[maxn], t[maxn];
int n, m, dp[maxn][maxn];

int solve(int l, int r) {
  if (l > r) return 1;
  if (dp[l][r] != -1) return dp[l][r];
  int ans = 0;
  if (l > m || t[l] == s[r - l + 1]) ans = add(ans, solve(l + 1, r));
  if (r > m || t[r] == s[r - l + 1]) ans = add(ans, solve(l, r - 1));
  return dp[l][r] = ans;
}

int main() {
  scanf("%s%s", s + 1, t + 1);
  n = strlen(s + 1); m = strlen(t + 1);
  ms(dp, -1);
  int ans = 0;
  for (int i = m; i <= n; i++) {
    ans = add(ans, solve(1, i));
  }
  printf("%d\n", ans);
  return 0;
}