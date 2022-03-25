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
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int d, mod = 998244353;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &d, &mod);
    if (d == 1) {
      printf("%d\n", 1 % mod);
      continue;
    }
    int hb = 31 - __builtin_clz(d), suf = d - (1 << hb) + 1;
    int ans = suf;
    for (int i = 31 - __builtin_clz(d); i > 0; i--) {
      int cnt = 1 << (i - 1);
      ans = (ans + 1ll * cnt * (1 + ans) % mod) % mod;
    }
    printf("%d\n", ans);
  }
  return 0;
}