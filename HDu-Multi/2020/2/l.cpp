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
const int maxn = 100000 + 5;

int n, m, q, nxt[maxn][26], nxt2[50][26];
char a[maxn], b[25], c[25];

int dp[25][25];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s%s", a + 1, b + 1);
    n = strlen(a + 1);
    m = strlen(b + 1);

    for (int j = 0; j < 26; j++) {
      nxt[n][j] = nxt[n + 1][j] = n + 1;
      nxt2[m][j] = nxt2[m + 1][j] = m + 1;
    }
    for (int i = n - 1; i >= 0; i--) {
      for (int j = 0; j < 26; j++) {
        nxt[i][j] = nxt[i + 1][j];
      }
      nxt[i][a[i + 1] - 'a'] = i + 1;
    }
    for (int i = m - 1; i >= 0; i--) {
      for (int j = 0; j < 26; j++) {
        nxt2[i][j] = nxt2[i + 1][j];
      }
      nxt2[i][b[i + 1] - 'a'] = i + 1;
    }

    scanf("%d", &q);
    while (q--) {
      int L, R;
      scanf("%d%d", &L, &R);
      if (R - L + 1 >= m) {
        for (int i = 0; i <= m; i++) {
          for (int j = 0; j <= i; j++) {
            dp[i][j] = n + 1;
          }
        }
        dp[0][0] = L - 1;
        for (int i = 0; i < m; i++) {
          for (int j = 0; j <= i; j++) {
            dp[i + 1][j + 1] = min(dp[i + 1][j + 1], nxt[dp[i][j]][b[i + 1] - 'a']);
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
          }
        }
        int diff = m;
        for (int j = 0; j <= m; j++) {
          if (dp[m][j] <= R) {
            diff = m - j;
          }
        }
        printf("%d\n", R - L + 1 - m + 2 * diff);
      } else {
        int len = R - L + 1;
        for (int i = L; i <= R; i++) {
          c[i - L + 1] = a[i];
        }
        c[len + 1] = 0;
        for (int i = 0; i <= len; i++) {
          for (int j = 0; j <= i; j++) {
            dp[i][j] = m + 1;
          }
        }
        dp[0][0] = 0;
        for (int i = 0; i < len; i++) {
          for (int j = 0; j <= i; j++) {
            dp[i + 1][j + 1] = min(dp[i + 1][j + 1], nxt2[dp[i][j]][c[i + 1] - 'a']);
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
          }
        }
        int diff = len;
        for (int j = 0; j <= len; j++) {
          if (dp[len][j] <= m) {
            diff = len - j;
          }
        }
        printf("%d\n", m - len + 2 * diff);
      }
    }
  }
  return 0;
}