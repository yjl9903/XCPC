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
const ll inf = 1ll << 60;
const int maxn = 5000 + 5;

int n, k, a[maxn];
ll sum[maxn], f[maxn], g[maxn], pre[maxn];

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    sum[i] = a[i] + sum[i - 1];
  }
  for (int t = 1; t <= k; t++) {
    ll pmx = f[t - 1] - sum[t - 1];
    for (int i = t; i <= n; i++) {
      g[i] = pmx + sum[i];
      pmx = max(pmx, pre[i] - sum[i]);
      if (i == t) {
        pre[i] = g[i];
      } else {
        pre[i] = max(g[i], pre[i - 1]);
      }
    }
    swap(f, g);
  }
  ll ans = -inf;
  for (int i = k; i <= n; i++) {
    ans = max(ans, f[i]);
  }
  printf("%lld\n", ans);
  return 0;
}