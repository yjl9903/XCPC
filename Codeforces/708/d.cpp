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

int n, tag[maxn], a[maxn];
ll f[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", tag + i);
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    for (int i = 1; i <= n; i++) {
      f[i] = 0;
    }
    ll ans = 0;
    for (int i = 2; i <= n; i++) {
      for (int j = i - 1; j >= 1; j--) {
        if (tag[i] == tag[j]) continue;
        ll fi = f[i], fj = f[j], w = abs(a[i] - a[j]);
        f[i] = max(f[i], fj + w);
        f[j] = max(f[j], fi + w);
        ans = max(ans, f[i]);
        ans = max(ans, f[j]);
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}