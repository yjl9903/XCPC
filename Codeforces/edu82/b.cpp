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
const int maxn = 100000 + 5;

int n, g, b;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &g, &b);
    if (n == 1) {
      puts("1"); continue;
    }
    int nd = (n + 1) / 2;
    int p = nd / g;
    ll ans = 1ll * p * g + 1ll * (p - 1) * b;
    if (nd % g != 0) {
      ans += b + nd % g;
    }
    if (ans < n) {
      printf("%d\n", n);
    } else {
      printf("%I64d\n", ans);
    }
  }
  return 0;
}