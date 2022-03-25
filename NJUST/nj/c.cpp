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
const ll inf = 1ll << 61;
const int maxn = 300000 + 5;

int n, k, a[maxn], q[maxn];
ll pre[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i];
    int l = 1, r = 0, ansl = 0, ansr = 0; ll ans = -inf;
    for (int i = 1; i <= n; i++) {
      while (l <= r && pre[i - 1] < pre[q[r]]) r--;
      q[++r] = i - 1;
      while (i - q[l] > k) l++;
      if (pre[i] - pre[q[l]] > ans) {
        ans = pre[i] - pre[q[l]];
        ansl = q[l] + 1; ansr = i;
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}