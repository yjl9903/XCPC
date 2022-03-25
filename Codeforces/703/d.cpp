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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, k, a[maxn], pre[maxn];

bool check(int x) {
  for (int i = 1; i <= n; i++) {
    pre[i] = pre[i - 1] + (a[i] >= x ? 1 : -1);
  }
  int mn = pre[0];
  for (int i = k; i <= n; i++) {
    if (pre[i] - mn > 0) return true;
    mn = min(mn, pre[i - k + 1]);
  }
  return false;
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  int l = 1, r = n, ans = -1;
  while (l <= r) {
    int m = (l + r) / 2;
    if (check(m)) {
      ans = m;
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  assert(ans != -1);
  printf("%d\n", ans);
  return 0;
}