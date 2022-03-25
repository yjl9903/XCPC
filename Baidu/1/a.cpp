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

int n, m, x[maxn], y[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    int ans = inf;
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", x + i, y + i);
      int need = (m + x[i] - 1) / x[i];
      ans = min(ans, need * y[i]);
    }
    printf("%d\n", ans);
  }
  return 0;
}