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
const int maxn = 1000000 + 5;

int n;
vector<int> last[50];
ll a[maxn], f[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", a + i);
  }
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= 40; j++) {
      for (int k = 0, p = (int)last[j].size() - 1; p >= 0 && k < 5; p--, k++) {
        int pre = last[j][p];
        f[i] = max(f[i], f[pre] + (a[i] & a[pre]));
        ans = max(ans, f[i]);
      }
    }
    for (int j = 0; j <= 40; j++) {
      if (a[i] >> j & 1) {
        last[j].push_back(i);
      }
    }
  }
  printf("%lld\n", ans);
  return 0;
}