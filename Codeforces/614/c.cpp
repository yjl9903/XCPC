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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 3000 + 5;

int n, siz[maxn][maxn], fa[maxn][maxn];
vector<int> edge[maxn];

ll dp[maxn][maxn];
ll solve(int a, int b) {
  if (dp[a][b] != -1) return dp[a][b];
  if (a == b) return 0;
  ll ans = 1ll * siz[a][b] * siz[b][a];
  return ans + max(solve(a, fa[a][b]), solve(b, fa[b][a]));
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    function<void(int,int)> dfs = [&](int u, int f) {
      siz[i][u] = 1; fa[i][u] = f;
      for (int v: edge[u]) {
        if (v == f) continue;
        dfs(v, u); siz[i][u] += siz[i][v];
      }
    };
    dfs(i, 0);
  }
  ll ans = 0; ms(dp, -1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      ans = max(ans, solve(j, i));
    }
  }
  cout << ans << endl;
  return 0;
}