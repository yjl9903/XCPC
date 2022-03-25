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
const int mod = 1000000007;
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

int f(int x) {
  return (1ll * x * (x + 1) / 2) % mod;
}
int g(int x) {
  return (1ll * x * (x + 1) * (2 * x + 1) / 6) % mod;
}

int n;
char s[maxn];

int main() {
  scanf("%d%s", &n, s + 1);
  int ans = 0;
  for (int i = 1, j; i <= n; i = j) {
    j = i + 1;
    if (s[i] == '0') continue;
    while (j <= n && s[j] == '0') j++;
    int zero = j - i;
    // dbg(i, zero);
    // dbg(f(i), f(zero), g(i));
    // ans = add(ans, mul(f(i), f(zero)));
    // ans = add(ans, mul(zero, sub(g(i), f(i))));
    int a = mul(i, f(zero));
    int b = mul(zero, f(i - 1));
    ans = add(ans, mul(i, add(a, b)));
  }
  printf("%d\n", ans);
  return 0;
}