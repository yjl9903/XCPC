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
const int maxn = 1000000 + 5;

int n, dp[maxn][2];
vector<int> edge[maxn];

ll ans;
void dfs(int u) {
  dp[u][0] = 1;
  for (int v: edge[u]) {
    dfs(v);
    ans += 1ll * dp[v][1] * dp[u][0] + 1ll * dp[v][0] * dp[u][1];
    dp[u][0] += dp[v][1];
    dp[u][1] += dp[v][0];
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 2, p; i <= n; i++) {
    scanf("%d", &p);
    edge[p].push_back(i);
  }
  dfs(1);
  cout << 2ll * ans << endl;
  return 0;
}