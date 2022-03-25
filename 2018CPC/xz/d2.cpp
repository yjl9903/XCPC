#include <bits/stdc++.h>
 
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
using namespace std;
 
const int N = 234;
const int md = 1e9 + 7;
 
int n, a[N], dp[N][N], sum[N][N];
char board[N][N];
 
inline void add(int &x, int y) {
  x += y;
  if (x >= md) {
    x -= md;
  }
}
 
inline void sub(int &x, int y) {
  x -= y;
  if (x < 0) {
    x += md;
  }
}
 
int main() {
#ifdef wxh010910
  freopen("input.txt", "r", stdin);
#endif
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      --a[i];
    }
    for (int i = 0; i < n; ++i) {
      scanf("%s", board[i]);
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        dp[i][j] = 0;
      }
    }
    int answer = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          sum[j + 1][k + 1] = board[a[j]][a[i]] == '1' ? dp[j][k] : 0;
          add(sum[j + 1][k + 1], sum[j + 1][k]);
          add(sum[j + 1][k + 1], sum[j][k + 1]);
          sub(sum[j + 1][k + 1], sum[j][k]);
        }
      }
      for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          if (a[i] == a[j] && a[i] == a[k]) {
            int ways = 1;
            add(ways, sum[j][k]);
            add(answer, ways);
            add(dp[j][k], ways);
            dbg(i + 1, j + 1, k + 1, dp[j][k], sum[j][k]);
          }
        }
      }
    }
    printf("%d\n", answer);
  }
  return 0;
}