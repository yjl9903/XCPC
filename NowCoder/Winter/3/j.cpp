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
const int inf = 1 << 30;
const int maxn = 200 + 5;

int n, m, k;
ll G[maxn][maxn];
vector< pair<ll,ll> > dp[maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      G[i][j] = 1e10;
    }
    G[i][i] = 0;
  }
  for (int i = 1, u, v; i <= m; i++) {
    scanf("%d%d", &u, &v);
    G[u][v] = G[v][u] = 1;
  }
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (G[i][k] < inf && G[k][j] < inf && G[i][k] + G[k][j] < G[i][j]) {
          G[i][j] = G[i][k] + G[k][j];
        }
      }
    }
  }
  scanf("%d", &k);
  vector< tuple<int,int,int> > pk;
  for (int i = 1; i <= k; i++) {
    int t, p, val;
    scanf("%d%d%d", &t, &p, &val);
    pk.emplace_back(t, p, val);
  }
  sort(begin(pk), end(pk));
  dp[1].push_back({0, 0});
  for (int i = 1; i <= k; i++) {
    int t, p, val; tie(t, p, val) = pk[i - 1];
    ll mxd = 0; int v = 0;
    for (int u = 1; u <= n; u++) {
      if (dp[u].empty()) continue;
      int rk = upper_bound(begin(dp[u]), end(dp[u]), make_pair(t - G[u][p], (ll)1e18)) - begin(dp[u]) - 1;
      if (rk >= 0) {
        mxd = max(mxd, dp[u][rk].second + val); v = t;
      }
    }
    if (v) {
      dp[p].push_back({ v, mxd });
    }
  }
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    for (auto& x: dp[i]) {
      ans = max(ans, x.second);
    }
  }
  cout << ans << endl;
  return 0;
}