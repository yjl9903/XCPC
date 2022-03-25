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

int n, f[maxn];
char s[maxn];

void dfs(int l, int r) {
  if (l == r) return ;
  int m = (l + r) / 2;
  dfs(l, m);
  int sum = 0, cur = s[m + 1] - '0', ten = 1, xs = 0;
  for (int i = m; i >= l; i--) {
    xs = add(xs, f[i]);
    sum = add(sum, mul(f[i], cur));
    ten = mul(ten, 10);
    cur = add(cur, mul(ten, s[i] - '0'));
  }
  for (int i = m + 1; i <= r; i++) {
    f[i] = add(f[i], sum);
    sum = mul(sum, 10);
    sum = add(sum, mul(s[i + 1] - '0', xs));
  }
  dfs(m + 1, r);
}

int main() {
  scanf("%d%s", &n, s + 1);
  f[0] = 1;
  dfs(0, n);
  printf("%d\n", f[n]);
  return 0;
}