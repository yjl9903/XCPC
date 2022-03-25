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
#ifdef XLor
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 2000 + 5;

int n, k, p, T, a[maxn], c[maxn];
ll sum[maxn][maxn], f[maxn][maxn];

ll cal(int i, int j) {
  if (i - j + 1 <= T) {
    ll cur = sum[j][i];
    if (j >= 3) {
      cur += f[j - 2][T - (i - j + 1)];
    }
    return cur;
  } else {
    return sum[i - T + 1][i];
  }
}

void dfs(int l, int r, int L, int R) {
  if (l > r) return ;
  int m = (l + r) / 2;
  int pos = -1;
  for (int i = max(L - 10, 1); i <= min(m, R + 10); i++) {
    if (pos == -1 || cal(m, i) > cal(m, pos)) {
      pos = i;
    }
  }
  // dbg(m, L, pos, R, cal(m, pos));
  // if (m >= 3) {
  //   dbg(cal(m, 3));
  // }
  f[m][T] = max(f[m][T], cal(m, pos));
  dfs(l, m - 1, L, pos);
  dfs(m + 1, r, pos, R);
}

int main() {
  scanf("%d%d%d", &n, &k, &p);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", c + i);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      sum[i][j] = sum[i][j - 1];
      sum[i][j] += 1ll * a[j] * c[j - i + 1];
    }
    for (int j = i; j <= n; j++) {
      sum[i][j] += p;
    }
  }
  for (int i = 1; i <= n; i++) {
    f[i][1] = max(1ll * a[i] * c[1] + p, f[i - 1][1]);
  }
  // T = 2;
  // for (int i = 1; i <= n; i++) {
  //   for (int j = i; j <= n; j++) {
  //     dbg(i, j, cal(j, i));
  //   }
  // }
  for (T = 2; T <= k; T++) {
    for (int i = 1; i <= n; i++) {
      f[i][T] = max(f[i][T - 1], sum[max(1, i - T + 1)][i]);
    }
    dfs(2, n, 1, n);
    for (int i = 1; i <= n; i++) {
      dbg(i, T, f[i][T]);
      f[i][T] = max(f[i][T], f[i - 1][T]);
    }
  }
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= k; j++) {
      ans = max(ans, f[i][j]);
    }
  }
  printf("%lld\n", ans);
  return 0;
}