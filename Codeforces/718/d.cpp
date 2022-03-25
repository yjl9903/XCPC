#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500 + 5;

int n, m, k, row[maxn][maxn], col[maxn][maxn], f[maxn][maxn][11];

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < m; j++) {
      scanf("%d", &row[i][j]);
    }
  }
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%d", &col[i][j]);
    }
  }
  if (k % 2 == 0) {
    k /= 2;
    for (int t = 1; t <= k; t++) {
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
          f[i][j][t] = inf;
          if (i > 1) {
            f[i][j][t] = min(f[i][j][t], f[i - 1][j][t - 1] + col[i - 1][j]);
          }
          if (i < n) {
            f[i][j][t] = min(f[i][j][t], f[i + 1][j][t - 1] + col[i][j]);
          }
          if (j > 1) {
            f[i][j][t] = min(f[i][j][t], f[i][j - 1][t - 1] + row[i][j - 1]);
          }
          if (j < m) {
            f[i][j][t] = min(f[i][j][t], f[i][j + 1][t - 1] + row[i][j]);
          }
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        printf("%d%c", 2 * f[i][j][k], " \n"[j == m]);
      }
    }
  } else {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        printf("-1%c", " \n"[j == m]);
      }
    }
  }
  return 0;
}