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
const int maxn = 500 + 5;

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
  int H(int n) {
    // Catalan
    return sub(C(2 * n, n), C(2 * n, n - 1));
  }
}
using Comb::C;

int n, K, m, f[maxn][maxn];
char S[maxn], T[maxn];

int main() {
  Comb::init();
  int Te; scanf("%d", &Te);
  while (Te--) {
    scanf("%d%d%d", &n, &K, &m);
    scanf("%s%s", S + 1, T + 1);
    int cnt1 = 0;
    for (int i = 1; i <= n; i++) {
      int x = S[i] - '0';
      int y = T[i] - '0';
      int v = x ^ y;
      if (v == 1) cnt1++;
    }
    ms(f, 0);
    f[0][0] = 1;
    for (int i = 1; i <= K; i++) {
      for (int j = 0; j <= n; j++) {
        // i - 1, j -> ...
        for (int k = 0; k <= j && k <= m; k++) {
          int cur = mul(mul(C(j, k), C(n - j, m - k)), f[i - 1][j]);
          f[i][j - k + m - k] = add(f[i][j - k + m - k], cur);
        }
      }
    }
    int ans = f[K][cnt1];
    ans = mul(ans, inv(C(n, cnt1)));
    printf("%d\n", ans);
  }
  return 0;
}