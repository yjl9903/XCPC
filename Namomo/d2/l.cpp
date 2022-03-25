#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, m, a[maxn], h[maxn];
ll ans;

ll cal(int i, int j) {
  return 1ll * (h[i] + h[j]) * (j - i);
}

void dfs(int l, int r, int L, int R) {
  if (l > r) return ;
  int m = (l + r) / 2;
  int pos = R;
  for (int i = R; i >= L && i > a[m]; i--) {
    if (cal(a[m], i) > cal(a[m], pos)) {
      pos = i;
    }
  }
  ans = max(ans, cal(a[m], pos));
  dfs(l, m - 1, L, pos);
  dfs(m + 1, r, pos, R);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", h + i);
  }
  for (int i = 1; i < n; i++) {
    if (h[i] > h[a[m]]) {
      a[++m] = i;
    }
  }
  dfs(1, m, 1, n);
  printf("%lld\n", ans);
  return 0;
}