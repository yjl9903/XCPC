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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

namespace sieve {
  const int maxp = 2000000 + 5;
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

ll f(ll x) {
  ll ans = 1;
  for (int i = 0; i < tot; i++) {
    if (x % prime[i]) continue;
    int c = 0;
    while (x % prime[i] == 0) {
      x /= prime[i]; c++;
    }
    ans *= c + 1;
  }
  if (x > 1) {
    ans *= 2;
  }
  return ans;
}

int main() {
  sieve::init();
  ll n; cin >> n;
  int ans = 0;
  while (n > 2) {
    n = f(n); ans++;
  }
  cout << ans << endl;
  return 0;
}