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
const int maxn = 200000 + 5;

int C, n;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &C, &n);
    double L = -inf, R = inf;
    for (int i = 1; i <= n; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      double delta = 1.0 * C * C * C * C - 100.0 * a * a - 20.0 * b * C * C;
      delta = sqrt(delta);
      L = max(L, 1.0 * (1.0 * C * C - delta) / (10.0 * a));
      R = min(R, 1.0 * (1.0 * C * C + delta) / (10.0 * a));
    }
    printf("%.8lf\n", (L + R) / 2);
  }
  return 0;
}