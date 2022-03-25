#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int, int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int m, cnt, Sqr;
int id1[maxn * 2], id2[maxn * 2], pri[maxn];
bool p[maxn];
ll w[maxn * 2];
ll pre[maxn];
ll g[maxn * 2], h[maxn * 2], s[maxn * 2];
void sieve(int n) {
  p[0] = p[1] = true;
  for (int i = 2; i <= n; i++) {
    if (!p[i]) pri[++cnt] = i, pre[cnt] = (pre[cnt - 1] + i) % mod;  // decided
    for (int j = 1; j <= cnt && 1ll * pri[j] * i <= n; j++) {
      p[i * pri[j]] = true;
      if (i % pri[j] == 0) break;
    }
  }
}
void init() {
  Sqr = sqrt(n);
  m = 0;
  ll i, j;
  for (i = 1; i <= n; i = j + 1) {
    w[++m] = n / i;
    g[m] = (w[m] + 1) % mod * (w[m] % mod) % mod;  // decided by f(x)
    if (g[m] & 1) g[m] += mod;
    g[m] /= 2, g[m]--;
    h[m] = (w[m] - 1) % mod;
    j = n / (n / i);
    if (w[m] <= Sqr)
      id1[w[m]] = m;
    else
      id2[n / w[m]] = m;
  }
  for (int i = 1; i <= cnt; i++) {
    for (int j = 1; 1ll * pri[i] * pri[i] <= w[j]; j++) {
      int k = (w[j] / pri[i] <= Sqr) ? id1[w[j] / pri[i]]
                                     : id2[n / (w[j] / pri[i])];
      g[j] = g[j] + mod - 1ll * pri[i] * (g[k] + mod - pre[i - 1]) % mod,
      g[j] %= mod;
      h[j] = h[j] + mod - (h[k] + mod - (i - 1)),
      h[j] %= mod;  // decided by f(x)
    }
  }
}
ll S(ll x, ll y) {
  if (x <= 1 || x < pri[y]) return 0;
  int k = x <= Sqr ? id1[x] : id2[n / x];
  ll res = g[k] - pre[y - 1] + mod - (h[k] - (y - 1));  // decided by f(x)
  res %= mod;
  if (y == 1) res += 2;  // decided by details
  for (int i = y; i <= cnt && 1ll * pri[i] * pri[i] <= x; i++) {
    ll t1 = pri[i], t2 = 1ll * pri[i] * pri[i];
    for (int e = 1; t2 <= x; e++, t1 = t2, t2 *= pri[i]) {
      res += (pri[i] ^ e) * S(x / t1, i + 1) % mod +
             (pri[i] ^ (e + 1));  // decided by f(x)
      res %= mod;
    }
  }
  return res;
}
// int main()
// {
//     sieve(max_n-1);
//     scanf("%lld",&n);
//     init();
//     printf("%lld\n",(1+S(n,1))%mod);
//     return 0;
// }

int main() {
  sieve(maxn - 1);
  init();
  return 0;
}