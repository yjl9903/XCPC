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

int n, ans, dp[maxn][2];
vector<int> edge[maxn];

void dfs(int u, int f) {
  dp[u][0] = dp[u][1] = 0;
  for (int v: edge[u]) {
    if (v == f) continue;
    dfs(v, u);
    dp[u][0] += dp[v][1];
    dp[u][1] += max(dp[v][0], dp[v][1]);
  }
  dp[u][0]++;
  ans = max(ans, max(dp[u][0], dp[u][1]));
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  dfs(1, 0);
  printf("%d\n", ans);
  return 0;
}