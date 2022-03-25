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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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

namespace sieve {
  const int maxp = 10000000 + 5;
  int vis[maxp], prime[maxp], divsor[maxp], cnt[maxp], tot;
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
using sieve::cnt;

int n, k, a[maxn], L[maxn][21], f[maxn][21];

int main() {
  sieve::init();
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      int val = 1;
      while (a[i] > 1) {
        int d = sieve::divsor[a[i]];
        int c = 0;
        while (a[i] % d == 0) {
          a[i] /= d;
          c ^= 1;
        }
        if (c == 1) {
          val *= d;
        }
      }
      a[i] = val;
      cnt[a[i]] = 0;
      dbg(a[i]);
    }
    for (int j = 0; j <= k; j++) {
      int l = n, val = 0;
      for (int i = n; i >= 1; i--) {
        while (l >= 1 && val + (cnt[a[l]] > 0) <= j) {
          val += cnt[a[l]] > 0;
          cnt[a[l]]++;
          l--;
        }
        L[i][j] = l;
        val -= cnt[a[i]] > 1;
        cnt[a[i]]--;
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int p = 0; p <= k; p++) {
        f[i][p] = p > 0 ? f[i][p - 1] : inf;
        for (int q = 0; q <= p; q++) {
          f[i][p] = min(f[i][p], f[L[i][p - q]][q] + 1);
        }
      }
    }
    int ans = inf;
    for (int j = 0; j <= k; j++) ans = min(ans, f[n][j]);
    printf("%d\n", ans);
  }
  return 0;
}