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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, k;

ll mul(int n, int k) {
  if (n == 1) return 1ll;
  if (k > maxn) return inf;
  ll r = 1;
  for (int i = 0; i < k; i++) {
    r *= n;
    if (r > inf) return inf;
  }
  return r;
}

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    if (k == 1) {
      printf("Case #%d: %d\n", ++kase, n);
    } else {
      ll ans = 0, L = 1;
      for (int i = 1; i <= n && L <= n; i++) {
        ll R = min(mul(i + 1, k) - 1, 1ll * n);
        ans += R / i - (L - 1) / i;
        L = R + 1;
      }
      printf("Case #%d: %lld\n", ++kase, ans);
    }
  }
  return 0;
}