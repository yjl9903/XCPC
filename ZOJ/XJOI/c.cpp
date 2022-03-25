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
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
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
const ll inf = 1ll << 60;
const int maxn = 2000 + 5;

int n, m, a[maxn], id[maxn], v[maxn], w[maxn];
ll cost[maxn], pre[maxn], dp[maxn][maxn];

ll solve(int l, int r) {
  if (dp[l][r] != -1) return dp[l][r];
  if (r <= a[1]) return 0;
  ll mn = inf;
  for (int c = 1; c < l; c++) {
    if (cost[c] == inf) continue;
    int lid = id[l - c], rid = id[r - c];
    ll val = cost[c] * (r - l + 1);
    if (lid != rid) {
      val += solve(l - c, a[lid]) + solve(a[rid - 1] + 1, r - c);
      val += pre[rid - 1] - pre[lid];
    } else if (l - c == a[lid - 1] + 1) {
      val += solve(l - c, a[lid]);
    } else if (r - c == a[rid]) {
      val += solve(a[rid - 1] + 1, r - c);
    } else if (r - c > a[1]) {
      continue;
    }
    mn = min(mn, val);
  }
  return dp[l][r] = mn;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      for (int j = a[i - 1] + 1; j <= a[i]; j++) {
        id[j] = i; cost[j] = inf;
      }
    }
    for (int i = 1; i <= a[n]; i++) {
      for (int j = i; j <= a[n]; j++) {
        dp[i][j] = -1;
      }
    }
    for (int i = 1; i <= m; i++) {
      scanf("%d%d", v + i, w + i);
    }
    for (int i = 1; i <= m; i++) {
      for (int j = w[i]; j <= a[n]; j++) {
        cost[j] = min(cost[j], cost[j - w[i]] + v[i]);
      }
    }
    for (int i = 2; i <= n; i++) {
      pre[i] = pre[i - 1] + solve(a[i - 1] + 1, a[i]);
    }
    if (pre[n] == inf) puts("-1");
    else printf("%lld\n", pre[n]);
  }
  return 0;
}