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
typedef long long ll;
typedef unsigned long long ull;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000 + 5;

int n, q, a[maxn][maxn], b[maxn][maxn];

int main() {
  while (scanf("%d%d", &n, &q) == 2) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        scanf("%d", &a[i][j]);
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        scanf("%d", &b[i][j]);
      }
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        ans += 1ll * a[i][j] * b[j][i];
      }
    }
    while (q--) {
      int k, x, y, v;
      scanf("%d%d%d%d", &k, &x, &y, &v);
      if (k == 0) {
        ans -= 1ll * a[x][y] * b[y][x];
        a[x][y] = v;
        ans += 1ll * a[x][y] * b[y][x];
      } else if (k == 1) {
        ans -= 1ll * a[y][x] * b[x][y];
        b[x][y] = v;
        ans += 1ll * a[y][x] * b[x][y];
      }
      printf("%I64d\n", ans);
    }
  }
  return 0;
}