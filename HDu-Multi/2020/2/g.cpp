#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
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
const int maxn = 200000 + 5;

struct Edge {
  int to, a, b;
};

int n, k, siz[maxn];
vector<Edge> edge[maxn];

ll dp[maxn][25];

bool check(ll L) {
  function<void(int,int)> dfs = [&](int u, int f) {
    siz[u] = 0;
    dp[u][0] = 0;
    vector<ll> tmp(k + 1, L + L);
    for (auto& x: edge[u]) {
      int v = x.to, A = x.a, B = x.b;
      if (v == f) continue;
      dfs(v, u);
      fill(begin(tmp), end(tmp), L + L);
      int sz = min(siz[u] + siz[v] + 1, k);
      for (int i = 0; i <= siz[u]; i++) {
        for (int j = 0; j <= siz[v] && i + j <= sz; j++) {
          if (dp[u][i] + dp[v][j] + B <= L) {
            tmp[i + j] = min(tmp[i + j], max(dp[u][i], dp[v][j] + B));
          }
          if (i + j + 1 <= k && dp[u][i] + dp[v][j] + A <= L) {
            tmp[i + j + 1] = min(tmp[i + j + 1], max(dp[u][i], dp[v][j] + A));
          }
        }
      }
      siz[u] = sz;
      for (int i = 0; i <= sz; i++) {
        dp[u][i] = tmp[i];
      }
    }
  };
  dfs(1, 0);
  return dp[1][k] <= L;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
    }
    ll l = 0, r = 0, ans = -1;
    for (int i = 2; i <= n; i++) {
      int u, v, a, b;
      scanf("%d%d%d%d", &u, &v, &a, &b);
      edge[u].push_back(Edge { v, a, b });
      edge[v].push_back(Edge { u, a, b });
      r += max(a, b);
    }
    while (l <= r) {
      ll mid = (l + r) / 2;
      if (check(mid)) {
        ans = mid; r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}