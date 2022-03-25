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
// inline int inv(int x) {
//   return qpow(x, mod - 2);
// }

int n, all, a[maxn], inv[maxn], suf[maxn];

int get(int sum) {
  if (suf[sum] != -1) return suf[sum];
  int cur = 0, lose = 1;
  for (int q = all; q >= sum; q--) {
    cur = add(cur, lose);
    lose = mul(lose, sub(1, mul(sum, inv[q])));
  }
  return suf[sum] = cur;
}

int main() {
  ms(suf, -1);
  inv[1] = 1;
  for (int i = 2; i < 2005; i++) {
    inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
  }

  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", a + i);
    all += a[i];
  }
  
  int ans = 0;
  for (int s = 1; s < (1 << n); s++) {
    int c = 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
      if (s >> i & 1) {
        c++;
        sum += a[i];
      }
    }
    int cur = get(sum);
    if (c % 2) ans = add(ans, cur);
    else ans = sub(ans, cur);
  }
  printf("%d\n", ans);
  return 0;
}