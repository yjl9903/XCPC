#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 2000 + 5;

int n, k, a[maxn];
double f[maxn][maxn], g[maxn];

int main() {
  int rp, rc;
  scanf("%d%d%d", &rp, &rc, &k);
  n = rc - rp;
  for (int i = 0; i <= k; i++) {
    scanf("%d", a + i);
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= k; j++) {
      f[i][j] = 1e18;
    }
  }
  f[1][0] = g[1] = 0.0;
  f[1][1] = a[1];
  for (int i = 2; i <= n; i++) {
    for (int k = 1; k < i; k++) {
      double cur = 1.0 * (i - k) / i * (g[i - k] + a[0]) + 1.0 * k / i * (g[k] + a[1]);
      f[i][1] = min(f[i][1], cur);
    }
    g[i] = f[i][1];
    for (int j = 2; j <= k; j++) {
      for (int k = 1; k < i; k++) {
        double cur = 1.0 * (i - k) / i * f[i - k][j - 1];
        cur += 1.0 * k / i * (a[j] + g[k]);
        f[i][j] = min(f[i][j], cur);
      }
      g[i] = min(g[i], f[i][j]);
    }
  }
  printf("%.8lf\n", g[n]);
  return 0;
}