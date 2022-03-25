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
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, t, a, b;

PII c[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &n, &t, &a, &b);
    int sa = 0, sb = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", &c[i].second);
      if (c[i].second == 0) {
        sa++;
      } else if (c[i].second == 1) {
        sb++;
      }
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", &c[i].first);
    }
    sort(c + 1, c + 1 + n);
    ll ans = 0, sum = 0;

    ll rest = c[1].first - 1;
    ll x = min(rest / a, 1ll * sa);
    rest -= x * a;
    ll y = min(rest / b, 1ll * sb);
    ans = max(ans, x + y);

    for (int i = 1; i <= n; i++) {
      if (c[i].second == 0) {
        sum += a; sa--;
      } else if (c[i].second == 1) {
        sum += b; sb--;
      }
      if (sum > t) break;
      if (i == n) {
        ans = i;
      } else if (sum < c[i + 1].first) {
        ll rest = c[i + 1].first - sum - 1;
        ll x = min(rest / a, 1ll * sa);
        rest -= x * a;
        ll y = min(rest / b, 1ll * sb);
        ans = max(ans, i + x + y);
      }
    }
    printf("%I64d\n", ans);
  }
  return 0;
}