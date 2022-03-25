#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <deque>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 20000 + 5;

int n, m, k, a[52][maxn];
ll pmx[maxn], smx[maxn], pre[52][maxn], dp[52][maxn];

ll qsum(int i, int l) {
  return pre[i][l + k - 1] - pre[i][l - 1];
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%d", &a[i][j]);
      pre[i][j] = a[i][j] + pre[i][j - 1];
    }
  }
  for (int t = 2; t <= n + 1; t++) {
    ll mxd = 0;
    for (int i = 1; i + k <= m + 1; i++) {
      mxd = max(mxd, dp[t - 2][i]);
      pmx[i] = max(pmx[i - 1], dp[t - 1][i]);
    }
    for (int i = m - k + 1; i >= 1; i--) {
      smx[i] = max(smx[i + 1], dp[t - 1][i]);
    }
    for (int i = 1; i + k <= m + 1; i++) {
      ll tot = mxd;
      if (i > k) tot = max(tot, pmx[i - k]);
      if (i + k <= m - k + 1) tot = max(tot, smx[i + k]);
      dp[t][i] = tot;
    }
    deque<int> dq;
    function<ll(int)> cal = [&](int i) -> ll {
      return dp[t - 1][i] + pre[t - 1][i - 1];
    };
    for (int i = m - k + 1; i >= 1; i--) {
      while (!dq.empty() && dq.front() - i >= k) dq.pop_front();
      while (!dq.empty() && cal(dq.back()) <= cal(i)) dq.pop_back();
      dq.push_back(i);
      dp[t][i] = max(dp[t][i], cal(dq.front()) - pre[t - 1][i + k - 1]);
    }
    while (!dq.empty()) dq.pop_back();
    cal = [&](int i) -> ll {
      return dp[t - 1][i] - pre[t - 1][i + k - 1];
    };
    for (int i = 1; i + k <= m + 1; i++) {
      while (!dq.empty() && i - dq.front() >= k) dq.pop_front();
      while (!dq.empty() && cal(dq.back()) <= cal(i)) dq.pop_back();
      dq.push_back(i);
      dp[t][i] = max(dp[t][i], cal(dq.front()) + pre[t - 1][i - 1]);
    }
    for (int i = 1; i + k <= m + 1; i++) {
      dp[t][i] += qsum(t, i) + qsum(t - 1, i);
    }
  }
  ll ans = 0;
  for (int i = 2; i <= n + 1; i++) {
    for (int j = 1; j + k <= m + 1; j++) {
      ans = max(ans, dp[i][j]);
    }
  }
  cout << ans << endl;
  return 0;
}