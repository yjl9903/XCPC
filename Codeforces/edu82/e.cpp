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
const int maxn = 500 + 5;

int n, m, nxt[maxn][26], dp[maxn][maxn];
char s[maxn], t[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s%s", s + 1, t + 1);
    n = strlen(s + 1); m = strlen(t + 1);
    for (int j = 0; j < 26; j++) nxt[n][j] = nxt[n + 1][j] = n + 1;
    for (int i = n - 1; i >= 0; i--) {
      for (int j = 0; j < 26; j++) nxt[i][j] = nxt[i + 1][j];
      nxt[i][s[i + 1] - 'a'] = i + 1;
    }
    auto solve = [&](int x) {
      for (int i = 0; i <= x; i++) {
        for (int j = x; j <= m; j++) {
          dp[i][j] = n + 1;
        }
      }
      dp[0][x] = 0;
      for (int i = 0; i <= x; i++) {
        for (int j = x; j <= m; j++) {
          if (dp[i][j] == n + 1) continue;
          dp[i + 1][j] = min(dp[i + 1][j], nxt[dp[i][j]][t[i + 1] - 'a']);
          dp[i][j + 1] = min(dp[i][j + 1], nxt[dp[i][j]][t[j + 1] - 'a']);
        }
      }
      return dp[x][m] <= n;
    };
    bool flag = false;
    for (int i = 1; i <= m && !flag; i++) {
      flag |= solve(i);
    }
    puts(flag ? "YES" : "NO");
  }
  return 0;
}