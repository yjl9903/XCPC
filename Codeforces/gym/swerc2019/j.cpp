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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
  return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}
inline int inv(int x) {
  return qpow(x, mod - 2);
}

namespace Comb {
  const int maxc = 2000000 + 5;
  int f[maxc], inv[maxc], finv[maxc];
  void init() {
    inv[1] = 1;
    for (int i = 2; i < maxc; i++)
      inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
    f[0] = finv[0] = 1;
    for (int i = 1; i < maxc; i++) {
      f[i] = f[i - 1] * 1ll * i % mod;
      finv[i] = finv[i - 1] * 1ll * inv[i] % mod;
    }
  }
  int C(int n, int m) {
    if (m < 0 || m > n) return 0;
    return f[n] * 1ll * finv[n - m] % mod * finv[m] % mod;
  }
  int H(int n) {
    return sub(C(2 * n, n), C(2 * n, n - 1));
  }
}
using Comb::C;

int n, a[maxn];

int dp[20][maxn];
void build() {
  for (int i = 1; i <= n; i++) dp[0][i] = i;
  for (int j = 1; j < 20; j++)
    for (int i = 1; i + (1 << j) <= n + 1; i++) {
      int l = dp[j - 1][i];
      int r = dp[j - 1][i + (1 << (j - 1))];
      if (a[l] <= a[r]) dp[j][i] = l;
      else dp[j][i] = r;
    }
}
int qmin(int l, int r) {
  int k = __lg(r - l + 1);
  int x = dp[k][l], y = dp[k][r - (1 << k) + 1];
  if (a[x] <= a[y]) return x;
  else return y;
}

int solve(int l, int r) {
  if (l >= r) return 1;
  int tot = qmin(l, r), mn = a[tot];
  int ans = solve(l, tot - 1), c = 1;
  while (tot < r) {
    int nx = qmin(tot + 1, r);
    if (a[nx] > mn) {
      ans = mul(ans, solve(tot + 1, r));
      break;
    } else if (a[nx] == mn) {
      ans = mul(ans, solve(tot + 1, nx - 1));
      tot = nx;
      c++;
    }
  }
  ans = mul(ans, Comb::H(c));
  return ans;
}

int main() {
  Comb::init();
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  if (n <= 1) {
    puts("1");
    return 0;
  }
  build();
  printf("%d\n", solve(1, n));
  return 0;
}