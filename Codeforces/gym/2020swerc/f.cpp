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
const int inf = 1 << 30;
const int maxn = 5000 + 5;

int R, n, mod;

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

int C[maxn][maxn];

int f[maxn][maxn], g[maxn];

int main() {
  scanf("%d%d%d", &R, &n, &mod);
  if (mod == 1) {
    puts("0");
    return 0;
  }
  C[0][0] = 1;
  for (int i = 1; i < maxn; i++) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; j++) {
      C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
    }
  }
  g[1] = 1;
  for (int i = 2; i <= n; i++) {
    g[i] = g[i - 1];
    for (int j = 1; i - 1 - j >= j; j++) {
      // j, i - 1 - j
      if (j < i - 1 - j) {
        g[i] = add(g[i], mul(C[i - 1][j], mul(g[j], g[i - 1 - j])));
      } else {
        g[i] = add(g[i], mul(C[i - 2][j], mul(g[j], g[j])));
      }
    }
  }
  f[1][1] = 1;
  for (int i = 2; i <= n; i++) {
    f[i][1] = g[i];
    f[i][i] = 0;
    for (int j = 2; j < i; j++) {
      int cur = 0;
      for (int k = 1; k < j; k++) {
        cur = add(cur, mul(C[j - 1][k], mul(g[k + 1], f[i - k][j - k])));
      }
      f[i][j] = sub(g[i], cur);
    }
  }
  printf("%d\n", f[n][R]);
  return 0;
}