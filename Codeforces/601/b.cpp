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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const ll inf = 1ll << 62;
const int maxn = 1000000 + 5;

int n, a[maxn];

ll calc(ll x) {
  ll pre = 0, ans = 0;
  for (int i = 1; i <= n; i++) {
    pre = (pre + a[i]) % x;
    ans += min(pre, x - pre);
  }
  return ans;
}

int main() {
  scanf("%d", &n);
  ll sum = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    sum += a[i];
  }
  ll ans = inf;
  for (int i = 2; 1ll * i * i <= sum; i++) {
    if (sum % i) continue;
    ans = min(ans, calc(i));
    while (sum % i == 0) sum /= i;
  }
  if (sum > 1) ans = min(ans, calc(sum));
  if (ans == inf) puts("-1");
  else printf("%I64d\n", ans);
  return 0;
}