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

int n, k, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    sort(a + 1, a + 1 + n, greater<int>());
    ll ans = 0;
    for (int i = 1; i <= k + 1; i++) ans += a[i];
    printf("%I64d\n", ans);
  }
  return 0;
}