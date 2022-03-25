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
using Comb::S;

int n, a[maxn], f[maxn][maxn];

int dfs(int l, int r) {
  if (l == r) return 1;
  if (f[l][r] != -1) return 1;
  int pos = l;
  for (int i = l; i <= r; i++) {
    if (a[i] < a[pos]) pos = i;
  }
  int suml = 1, sumr = 1;
  int cnt = 1, mx = a[pos];
  for (int i = pos - 1; i >= l; i--) {
    int cur = dfs(l, i);
    cur = mul(cur, S(cnt, pos - i - 1));
    suml = add(suml, cur);
    if (a[i] > mx) {
      mx = a[i];
      cnt++;
    }
  }
  // suml = add(suml, S(cnt, pos - l));
  cnt = 1; mx = a[pos];
  for (int i = pos + 1; i <= r; i++) {
    int cur = dfs(i, r);
    cur = mul(cur, S(cnt, i - pos - 1));
    sumr = add(sumr, cur);
    if (a[i] > mx) {
      mx = a[i];
      cnt++;
    }
  }
  // sumr = add(sumr, S(cnt, r - pos));
  dbg(l, r);
  dbg(suml, sumr);
  return f[l][r] = mul(suml, sumr);
}

int main() {
  Comb::init();
  scanf("%d", &n);
  ms(f, -1);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  cout << dfs(1, n) << endl;
  return 0;
}