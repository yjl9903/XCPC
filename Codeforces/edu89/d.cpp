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
const int maxn = 500000 + 5;

int n;
PII ans[maxn];

namespace sieve {
  const int maxp = 10000000 + 5;
  int vis[maxp], divsor[maxp], prime[maxp], tot;
  void init() {
    ms(vis, 0);
    for (int i = 2; i < maxp; i++) {
      if (!vis[i]) prime[tot++] = i, divsor[i] = i;
      for (int j = 0; j < tot && prime[j] * i < maxp; j++) {
        vis[i * prime[j]] = 1;
        divsor[i * prime[j]] = prime[j];
        if (i % prime[j] == 0) break;
      }
    }
  }
}

int main() {
  sieve::init();
  scanf("%d", &n);
  for (int i = 1, x; i <= n; i++) {
    scanf("%d", &x);
    int d = sieve::divsor[x];
    while (x % d == 0) x /= d;
    if (x == 1) {
      ans[i] = { -1, -1 };
    } else {
      ans[i] = { d, x };
    }
  }
  for (int i = 1; i <= n; i++) {
    printf("%d ", ans[i].first);
  }
  puts("");
  for (int i = 1; i <= n; i++) {
    printf("%d ", ans[i].second);
  }
  return 0;
}