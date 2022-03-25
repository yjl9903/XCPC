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
const int maxn = 8000 + 5;

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

int n, f[maxn], a[maxn], cnt[maxn], dp[maxn];

int main() {
  scanf("%d", &n);
  f[0] = 1;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    cnt[a[i]]++;
    f[i] = mul(f[i - 1], i);
  }
  dp[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = i - 1; j >= 0; j--) {
      int tot = mul(dp[j], cnt[i]);
      dp[j + 1] = add(dp[j + 1], tot);
    }
  }
  int ans = 0;
  for (int i = 0; i <= n; i++) {
    int tot = mul(dp[i], f[n - i]);
    if (i % 2 == 0) {
      ans = add(ans, tot);
    } else {
      ans = sub(ans, tot);
    }
    dbg(i, mul(dp[i], f[n - i]));
  }
  printf("%d\n", ans);
  return 0;
}