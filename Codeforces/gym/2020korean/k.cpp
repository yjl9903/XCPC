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
const int maxn = 500 + 5;

ll a[maxn][maxn];
ll c[maxn][maxn];
int n, q;

ll quickmodow(ll x, ll y) {
  ll cur = x, ret = 1ll;
  for (int i = 0; y; i++) {
    if (y & (1ll << i)) {
      y -= (1ll << i);
      ret = ret * cur % mod;
    }
    cur = cur * cur % mod;
  }
  return ret;
}
ll mulinv(ll x) {
  return quickmodow(x, mod - 2);
}

void gauss() {
  for (int i = 1; i <= n; i++) {
    if (a[i + 1][i] == 0) {
      bool found = false;
      for (int j = i + 2; j <= n; j++) {
        if (a[j][i] != 0) {
          for (int k = i; k <= n; k++) swap(a[i + 1][k], a[j][k]);
          for (int k = 1; k <= n; k++) swap(a[k][i + 1], a[k][j]);
          found = false;
          break;
        }
      }
      if (found) {
        continue;
      }
    }
    for (int j = i + 2; j <= n; j++) {
      ll coe = mod - a[j][i] * mulinv(a[i + 1][i]) % mod;
      for (int k = i; k <= n; k++) a[j][k] = (a[j][k] + coe * a[i + 1][k] % mod) % mod;
      for (int k = 1; k <= n; k++)
        a[k][i + 1] = (a[k][i + 1] - coe * a[k][j] % mod + mod) % mod;
    }
  }
}

void charmodoly() {
  c[0][0] = 1ll;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      c[i][j] = (c[i - 1][j - 1] - a[i][i] * c[i - 1][j] % mod + mod) % mod;
    }
    ll coe = mod - 1, cur = mod - a[i][i - 1] % mod;
    for (int j = i - 2; j >= 0; j--) {
      ll tmmod = cur * (mod - a[j + 1][i]) % mod;
      tmmod = coe * tmmod % mod;
      for (int k = 0; k <= j; k++) {
        c[i][k] = (c[i][k] + c[j][k] * tmmod % mod) % mod;
      }
      cur = cur * (mod - a[j + 1][j]) % mod;
      coe = mod - coe % mod;
    }
    for (int k = 0; k <= i; k++) c[i][k] %= mod;
  }
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      scanf("%lld", &a[i][j]);
    }
  }
  gauss();
  charmodoly();
  // for (int i = 0; i <= n; i++) {
  //   printf("%d%c", c[n][i], " \n"[i == n]);
  // }
  while (q--) {
    int x;
    scanf("%d", &x);
    ll ans = 0;
    ll base = 1;
    for (int i = 0; i <= n; i++) {
      ans = (ans + base * c[n][i] % mod) % mod;
      base = base * x % mod;
    }
    if (n % 2 == 1)
      printf("%lld%c", (mod - ans) % mod, " \n"[q == 0]);
    else
      printf("%lld%c", ans, " \n"[q == 0]);
  }
  return 0;
}