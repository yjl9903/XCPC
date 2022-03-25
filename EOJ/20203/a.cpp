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

int k;
ll n, m;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%lld%lld", &k, &n, &m);
    ll ans[4] = { (ll)5e18, (ll)5e18, (ll)5e18, (ll)5e18 };
    for (int i = 1; i <= k; i++) {
      ll x, y;
      scanf("%lld%lld", &x, &y);
      ans[0] = min(ans[0], abs(x) + abs(y));
      ans[1] = min(ans[1], abs(x) + abs(y - m));
      ans[2] = min(ans[2], abs(x - n) + abs(y));
      ans[3] = min(ans[3], abs(x - n) + abs(y - m));
    }
    printf("%lld\n", *max_element(ans, ans + 4));
  }
  return 0;
}