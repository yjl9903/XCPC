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
    int p, q, a, b;
    scanf("%d%d%d%d", &p, &q, &a, &b);
    ll lhs = -1ll * (100 - p) * q + 1ll * (100 - q) * p * b * a;
    ll rhs = -1ll * (100 - q) * p * b + 1ll * (100 - p) * q * b;
    if (lhs <= 0) {
      puts("-1");
    } else {
      printf("%d\n", (rhs + lhs - 1) / lhs);
    }
  }
  return 0;
}