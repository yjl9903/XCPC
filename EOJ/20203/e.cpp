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
const int maxn = 1000000 + 5;

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
inline int Inv(int x) {
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
int n, m, a[maxn];

int main() {
  Comb::init();
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    sort(a + 1, a + 1 + n);
    int ans = 0;
    for (int i = m; i <= n; i++) {
      int tot = mul(C(i - 1, m - 1), a[i]);
      ans = add(ans, tot);
    }
    printf("%d\n", ans);
  }
  return 0;
}