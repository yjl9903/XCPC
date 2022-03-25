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

ll a, b, n;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%I64d%I64d%I64d", &a, &b, &n);
    int ans = 0;
    while (a <= n && b <= n) {
      if (a < b) {
        a += b;
      } else {
        b += a;
      }
      ans++;
    }
    printf("%d\n", ans);
  }
  return 0;
}