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

int n, m, a[maxn];

int main() {
  scanf("%d%d", &n, &m);
  ll sum = 0;
  for (int i = 1; i <= m; i++) {
    scanf("%d", a + i);
    sum += a[i];
  }
  if (sum < n) {
    puts("-1");
    return 0;
  }
  vector<ll> ans = { 1 };
  sum -= a[1];
  int tot = a[1];
  for (int i = 2; i <= m; i++) {
    if (tot + sum == n) {
      ans.push_back(tot + 1);
      tot += a[i];
    } else if (tot + sum < n) {
      puts("-1");
      return 0;
    } else {
      ll pos = max(ans.back() + 1, tot + 1 - (tot + sum - n));
      ans.push_back(pos);
      tot = pos + a[i] - 1;
      if (tot > n) {
        puts("-1");
        return 0;
      }
    }
    sum -= a[i];
  }
  for (ll x: ans) printf("%I64d ", x);
  return 0;
}