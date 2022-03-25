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
const int mod = 1e9 + 7;
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

int n, a[maxn], pre[maxn], pre2[maxn], suf2[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    pre[0] = pre2[0] = suf2[n + 1] = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      pre[i] = add(pre[i - 1], a[i]);
      pre2[i] = add(pre2[i - 1], mul(i, a[i]));
    }
    for (int i = n; i >= 1; i--) {
      suf2[i] = add(suf2[i + 1], mul(n - i + 1, a[i]));
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      int cur = 0;
      if (i + i <= n) {
        cur = add(cur, pre2[i]);
        cur = add(cur, suf2[n - i + 1]);
        int L = i + 1, R = n - i;
        if (L <= R) {
          cur = add(cur, mul(i, sub(pre[R], pre[L - 1])));
        }
      } else {
        cur = add(cur, pre2[n - i + 1]);
        cur = add(cur, suf2[i]);
        if (i == n - i + 1) {
          cur = sub(cur, mul(i, a[i]));
        }
        int L = n - i + 2, R = i - 1;
        if (L <= R) {
          cur = add(cur, mul(n - i + 1, sub(pre[R], pre[L - 1])));
        }
      }
      // dbg(i, cur);
      ans = add(ans, mul(cur, inv(i)));
    }
    ans = mul(ans, mul(2, mul(inv(n), inv(n + 1))));
    printf("%d\n", ans);
  }
  return 0;
}