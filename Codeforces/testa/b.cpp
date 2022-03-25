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

int n, m, k, a[maxn], last[maxn], last2[maxn];

int op[maxn], x[maxn], y[maxn];
PII f[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &m, &k);
    f[1] = {
      sub(1, mul(mul(n + n, inv(n)), inv(n - 1))),
      mul(2, mul(inv(n), inv(n - 1)))
    };
    for (int i = 2; i <= m; i++) {
      f[i] = {
        mul(f[1].first, f[i - 1].first),
        add(mul(f[1].first, f[i - 1].second), f[1].second)
      };
      // dbg(i, f[i].first, f[i].second);
    }
    auto eval = [&](int i, int x) {
      return add(mul(f[i].first, x), f[i].second);
    };
    auto upd = [&](int i, int t) {
      if (t <= 0) return ;
      a[i] = eval(t, a[i]);
    };
    for (int i = 1; i <= n; i++) {
      a[i] = last[i] = last2[i] = 0;
    }
    a[1] = 1;
    for (int i = 1; i <= k; i++) {
      scanf("%d%d%d", op + i, x + i, y + i);
    }
    for (int i = 1, p = 1; i <= m; i++) {
      if (p <= k && op[p] == i) {
        int x = ::x[p], y = ::y[p];
        upd(x, i - 1 - last[x] - (p - 1 - last2[x]));
        upd(y, i - 1 - last[y] - (p - 1 - last2[y]));
        swap(a[x], a[y]);
        last[x] = last[y] = i;
        last2[x] = last2[y] = p;
        p++;
      }
    }
    for (int i = 1; i <= n; i++) {
      upd(i, m - last[i] - (k - last2[i]));
      printf("%d%c", a[i], " \n"[i == n]);
    }
  }
  return 0;
}