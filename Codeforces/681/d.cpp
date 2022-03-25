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
const int maxn = 3000 + 5;

int n, k, cnt[maxn];
ll sum[maxn];
vector<int> bag[maxn];

ll dp[maxn << 2][maxn];
ll dfs(int l, int r, int rt) {
  if (l == r) {
    ll ans = dp[rt][k], cur = 0;
    for (int i = 0; i < bag[l].size() && i + 1 <= k; i++) {
      cur += bag[l][i];
      ans = max(ans, cur + dp[rt][k - i - 1]);
    }
    return ans;
  }
  int m = (l + r) / 2;
  memcpy(dp[rt << 1], dp[rt], sizeof dp[rt]);
  memcpy(dp[rt << 1 | 1], dp[rt], sizeof dp[rt]);
  for (int i = l; i <= m; i++) {
    for (int j = k; j >= cnt[i]; j--) {
      dp[rt << 1 | 1][j] = max(dp[rt << 1 | 1][j], dp[rt << 1 | 1][j - cnt[i]] + sum[i]);
    }
  }
  for (int i = m + 1; i <= r; i++) {
    for (int j = k; j >= cnt[i]; j--) {
      dp[rt << 1][j] = max(dp[rt << 1][j], dp[rt << 1][j - cnt[i]] + sum[i]);
    }
  }
  return max(dfs(l, m, rt << 1), dfs(m + 1, r, rt << 1 | 1));
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", cnt + i);
    for (int j = 0; j < cnt[i]; j++) {
      int x;
      scanf("%d", &x);
      bag[i].push_back(x);
      sum[i] += x;
    }
  }
  ll ans = dfs(1, n, 1);
  printf("%lld\n", ans);
  return 0;
}