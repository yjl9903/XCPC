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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 50 + 5;

int n, m, dp[maxn][maxn];
char s[maxn][maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s[i] + 1);
  }
  dp[1][1] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (s[i][j] == 'R') {
        dp[i][j + 1] = (dp[i][j + 1] + dp[i][j]) % mod;
      } else if (s[i][j] == 'D') {
        dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % mod;
      } else if (s[i][j] == 'B') {
        dp[i][j + 1] = (dp[i][j + 1] + dp[i][j]) % mod;
        dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % mod;
      }
    }
  }
  cout << dp[n][m] << endl;
  return 0;
}