#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int maxn = 500 + 5;

ll n, mod;

ll add(ll x, ll y) {
  x += y;
  return x >= mod ? x - mod : x;
}
ll sub(ll x, ll y) {
  x -= y;
  return x < 0 ? x + mod : x;
}
ll mul(ll x, ll y) {
  return ll(__int128(1) * x * y % mod);
}
ll qpow(ll x, ll n) {
  ll r = 1;
  while (n) {
    if (n % 2 == 1) r = mul(r, x);
    x = mul(x, x);
    n /= 2;
  }
  return r;
}
ll inv(ll x) {
  return qpow(x, mod - 2);
}

ll a[maxn][maxn], B[maxn][maxn];
int cnt[maxn];

int main() {
  cin >> n >> mod;
  for (int i = 1; i <= n + 1; i++) {
    a[1][i] = 1;
  }
  for (int i = 2; i <= n; i++) {
    memset(cnt, 0, sizeof cnt);
    for (int j = 1; j <= n; j++) {
      cnt[__gcd(i, j)]++;
    }
    a[i][n + 1] = 1;
    for (int j = 1; j <= n; j++) {
      if (j == i) {
        a[i][j] = mul(n - cnt[j], inv(n));
      } else {
        a[i][j] = mul(mod - cnt[j], inv(n));
      }
      // cout << cnt[j] << ' ';
    }
    // cout << endl;
  }
  // for (int i = 1; i <= n; i++) {
  //   for (int j = 1; j <= n + 1; j++) {
  //     printf("%2d ", a[i][j]);
  //   }
  //   puts("");
  // }
  // for (int i = 1; i <= n; i++) {
  //   ll B = inv(a[i][i]);
  //   for (int j = 1; j <= n; j++) {
  //     if (i == j) continue;
  //     ll xs = mul(B, a[j][i]);
  //     for (int k = 1; k <= n; k++) {
  //       a[j][k] = sub(a[j][k], mul(xs, a[i][k]));
  //     }
  //   }
  // }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n + 1; j++) {
      printf("%10lld ", a[i][j]);
    }
    puts("");
  }
  return 0;
}