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
const int maxn = 6000 + 5;

int n, L[maxn], R[maxn];
vector<int> lsh, edge[maxn];

int dp[maxn][maxn], mn[maxn];
void dfs(int u, int f) {
  for (int v: edge[u]) {
    if (v == f) continue;
    dfs(v, u);
  }

  mn[u] = inf;
  int tot = inf;
  for (int i = 0; i + 1 < lsh.size(); i++) {
    int& cur = dp[u][i];
    if (L[u] <= lsh[i] && lsh[i + 1] - 1 <= R[u]) {
      cur = 0;
      for (int v: edge[u]) {
        if (v == f) continue;
        int val = min(dp[v][i], 1 + mn[v]);
        cur += val;
      }
      tot = min(tot, cur);
    }
  }
  for (int i = 0; i + 1 < lsh.size(); i++) {
    int& cur = dp[u][i];
    if (L[u] <= lsh[i] && lsh[i + 1] - 1 <= R[u]) {

    } else {
      cur = 1 + tot;
    }
  }
  for (int i = 0; i + 1 < lsh.size(); i++) {
    int& cur = dp[u][i];
    mn[u] = min(mn[u], cur);
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    lsh = { 0, 1 };
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
    }
    for (int i = 2; i <= n; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      edge[u].push_back(v);
      edge[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", L + i, R + i);
      lsh.push_back(L[i]);
      lsh.push_back(R[i] + 1);
    }
    sort(begin(lsh), end(lsh));
    lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
    dfs(1, 0);
    int ans = inf;
    for (int i = 0; i + 1 < (int)lsh.size(); i++) {
      // dbg(i, lsh[i], dp[1][i]);
      if (lsh[i] == 0) {
        ans = min(ans, dp[1][i]);
      } else {
        ans = min(ans, 1 + dp[1][i]);
      }
    }
    assert(0 <= ans && ans <= n);
    printf("%d\n", ans);
  }
  return 0;
}