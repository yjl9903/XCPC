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

int n, m;

ll C(int n) {
  return 1ll * n * (n + 1) / 2;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    n -= m;
    int len = n / (m + 1);
    int c1 = n % (m + 1);
    ll ans = 1ll * c1 * C(len + 1) + 1ll * (m + 1 - c1) * C(len);
    printf("%I64d\n", C(n + m) - ans);
  }
  return 0;
}