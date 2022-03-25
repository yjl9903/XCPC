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
typedef long long ll;
typedef pair<int,int> PII;
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

namespace Comb {
    const int maxc = 2000000 + 5;
    int f[maxc], inv[maxc], finv[maxc];
    void init() {
        inv[1] = 1;
        for (int i = 2; i < maxc; i++)
            inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
        f[0] = finv[0] = 1;
        for (int i = 1; i < maxc; i++) {
            f[i] = f[i - 1] * 1ll * i % mod;
            finv[i] = finv[i - 1] * 1ll * inv[i] % mod;
        }
    }
    int C(int n, int m) {
        if (m < 0 || m > n) return 0;
        return f[n] * 1ll * finv[n - m] % mod * finv[m] % mod;
    }
    int S(int n, int m) {
        // x_1 + x_2 + ... + x_n = m, x_i >= 0
        if (n == 0 && m == 0) return 1;
        return C(m + n - 1, n - 1);
    }
}
using Comb::C;

int n, k, d, dp[200][200];

int main() {
  Comb::init();
  scanf("%d%d%d", &n, &k, &d);
  dp[0][0] = 1;
  int ans = 0;
  for (int i = 1; i <= k; i++) {
    for (int j = n; j >= 1; j--) {
      for (int use = 1; use <= n; use++) {
        for (int use2 = use; use2 >= 1; use2--) {
          if (j < use2 * i) continue;
          dp[use][j] = add(dp[use][j], mul(dp[use - use2][j - use2 * i], C(use, use2)));
        }
      }
    }
    if (i == d - 1) {
      for (int use = 1; use <= n; use++) {
        ans = sub(ans, dp[use][n]);
      }
    }
  }
  for (int use = 1; use <= n; use++) {
    ans = add(ans, dp[use][n]);
  }
  cout << ans;
  return 0;
}