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
const int maxn = 200 + 5;

int n, m, a[maxn][maxn], sum[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        scanf("%d", &a[i][j]);
      }
    }
    for (int j = 0; j <= m; j++) {
      sum[j] = 0;
    }
    double ans = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        sum[j] += a[i][j];
        ans = max(ans, 1.0 * sum[j] / a[i][j]);
      }
    }
    printf("%.8lf\n", ans);
  }
  return 0;
}