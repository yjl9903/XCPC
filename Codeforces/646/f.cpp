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
const int maxn = 2000 + 5;

int n, dp[maxn][maxn], sufs[maxn][26], suft[maxn][26];
char s[maxn], t[maxn];

int solve(int x, int y) {
  if (x == 0) return 0;
  if (dp[x][y] != -1) return dp[x][y];
  int ans = inf;

  if (s[x] == s[y]) {
    ans = min(ans, solve(x - 1, y - 1));
  }
  
  return dp[x][y] = ans;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%s%s", &n, s + 1, t + 1);
    for (int i = 0; i <= n + 1; i++) {
      for (int j = 0; j <= n + 1; j++) {
        dp[i][j] = -1;
      }
      for (int c = 0; c < 26; c++) {
        sufs[i][c] = 0;
        suft[i][c] = 0;
      }
    }
    for (int i = n; i >= 1; i--) {
      for (int c = 0; c < 26; c++) {
        sufs[i][c] = sufs[i + 1][c];
        suft[i][c] = suft[i + 1][c];
      }
      sufs[i][s[i] - 'a']++;
      suft[i][t[i] - 'a']++;
    }
    int ans = solve(n, n);
    if (ans >= inf) {
      puts("-1");
    } else {
      printf("%d\n", ans);
    }
  }
  return 0;
}