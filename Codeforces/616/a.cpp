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
const int maxn = 100000 + 5;

int n, m, k, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    int ans = 0;
    k = min(k, m - 1);
    for (int i = 0; i <= k; i++) {
      int j = n - (k - i) + 1;
      int rest = m - k;
      int tot = inf;
      for (int l = 1; l <= rest; l++) {
        tot = min(tot, max(a[i + l], a[j - (rest - l) - 1]));
      }
      assert(tot != inf);
      ans = max(ans, tot);
    }
    printf("%d\n", ans);
  }
  return 0;
}