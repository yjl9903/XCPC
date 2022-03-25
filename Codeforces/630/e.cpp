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
const int maxn = 200000 + 5;

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

int n, m;

int main() {
  int L, R;
  scanf("%d%d%d%d", &n, &m, &L, &R);
  if (L == R) {
    puts("1");
    return 0;
  }
  int ans = qpow(R - L + 1, 1ll * n * m);
  if (n % 2 == 0 || m % 2 == 0) {
    int even = R / 2 - (L - 1)  / 2, odd = (R - L + 1) - even;
    int a = qpow(even + odd, 1ll * n * m);
    int b = qpow(abs(odd - even), 1ll * n * m);
    ans = sub(ans, mul(sub(a, b), inv(2)));
  }
  printf("%d\n", ans);
  return 0;
}