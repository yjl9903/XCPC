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
const int maxn = 300000 + 5;

int n;
ll a[maxn], b[maxn], pre[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%I64d%I64d", a + i, b + i);
    }
    if (n == 1) {
      printf("%I64d\n", a[1]);
      continue;
    }
    pre[1] = max(a[1] - b[n], 0ll);
    for (int i = 2; i <= n; i++) {
      pre[i] = pre[i - 1] + max(a[i] - b[i - 1], 0ll);
    }
    ll ans = a[n] + pre[n - 1], suf = max(a[n] - b[n - 1], 0ll);
    for (int i = n - 1; i >= 1; i--) {
      ans = min(ans, pre[i - 1] + a[i] + suf);
      suf += max(a[i] - b[i - 1], 0ll);
    }
    printf("%I64d\n", ans);
  }
  return 0;
}