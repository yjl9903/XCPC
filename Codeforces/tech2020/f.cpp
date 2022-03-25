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
#include <random>
#include <ctime>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

mt19937 rnd(time(nullptr));

namespace sieve{
  const int maxp = 1000000 + 5;
  int vis[maxp], prime[maxp], tot;
  void init() {
    ms(vis, 0);
    for (int i = 2; i < maxp; i++) {
      if (!vis[i]) prime[tot++] = i;
      for (int j = 0; j < tot && prime[j] * i < maxp; j++) {
        vis[i * prime[j]] = 1;
        if (i % prime[j] == 0) break;
      }
    }
  }
}
using sieve::prime;
using sieve::tot;

int n, p[maxn];
ll a[maxn], ans;

ll cal(ll p) {
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    if (a[i] < p) {
      ans += p - a[i];
    } else {
      ans += min(a[i] % p, p - a[i] % p);
    }
    if (ans > ::ans) return ans;
  }
  return ans;
}

ll solve(ll x) {
  ll ans = n;
  for (int i = 0; i < tot && 1ll * prime[i] * prime[i] <= x; i++) {
    if (x % prime[i]) continue;
    while (x % prime[i] == 0) x /= prime[i];
    ans = min(ans, cal(prime[i]));
  }
  if (x > 1) ans = min(ans, cal(x));
  return ans;
}

int main() {
  sieve::init();
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%I64d", a + i);
    p[i] = i;
  }
  shuffle(p + 1, p + 1 + n, rnd);
  ans = n;
  clock_t st = clock();
  for (int i = 1; i <= n && clock() - st < 2.0 * CLOCKS_PER_SEC; i++) {
    ans = min(ans, solve(a[p[i]]));
    ans = min(ans, solve(a[p[i]] + 1));
    if (a[p[i]] > 1) {
      ans = min(ans, solve(a[p[i]] - 1));
    }
  }
  printf("%I64d\n", ans);
  return 0;
}