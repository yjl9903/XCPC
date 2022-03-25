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
const int maxn = 200 + 5;

int n, m, L[maxn][maxn], R[maxn][maxn], dp[maxn][maxn];

int solve(int l, int r) {
  if (l > r) return 0;
  if (dp[l][r] != -1) return dp[l][r];
  int& ans = dp[l][r];
  for (int j = l; j <= r; j++) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
      if (l <= L[i][j] && R[i][j] <= r) {
        cnt++;
      }
    }
    ans = max(ans, cnt * cnt + solve(l, j - 1) + solve(j + 1, r));
  }
  return ans;
}

int main() {
  ms(dp, -1);
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    int k; scanf("%d", &k);
    while (k--) {
      int l, r; scanf("%d%d", &l, &r);
      for (int j = l; j <= r; j++) {
        L[i][j] = l;
        R[i][j] = r;
      }
    }
  }
  printf("%d\n", solve(1, m));
  return 0;
}