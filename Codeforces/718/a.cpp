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



int main() {
  int T; scanf("%d", &T);
  while (T--) {
    ll n;
    scanf("%lld", &n);
    if (n % 2050 == 0) {
      n /= 2050;
      int ans = 0;
      while (n) {
        ans += n % 10;
        n /= 10;
      }
      printf("%d\n", ans);
    } else {
      puts("-1");
    }
  }
  return 0;
}