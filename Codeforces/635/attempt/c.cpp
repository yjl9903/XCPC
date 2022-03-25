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
const int maxn = 3000 + 5;

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
  return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}
inline int inv(int x) {
  return qpow(x, mod - 2);
}

char s[maxn], t[maxn];
int n, m, fail[maxn], nxt[maxn][26], nxt2[maxn][26], dp[maxn][maxn];

void build() {
  fail[1] = 0;
  for (int i = 2; i <= m; i++) {
    int cur = fail[i - 1];
    while (cur && t[cur + 1] != t[i]) cur = fail[cur];
    if (t[cur + 1] == t[i]) cur++;
    fail[i] = cur;
  }
  for (int i = 0; i <= m; i++) {
    for (int ch = 0; ch < 26; ch++) {
      int cur = i;
      while (cur && t[cur + 1] != ch + 'a') cur = fail[cur];
      if (t[cur + 1] == ch + 'a') cur++;
      nxt[i][ch] = cur;
    }
  }
}

int main() {
  scanf("%s%s", s + 1, t + 1);
  n = strlen(s + 1); m = strlen(t + 1);
  reverse(t + 1, t + 1 + m);
  int mx = 1;
  while (mx <= m && t[mx] == t[1]) mx++;
  mx--;
  build();
  dp[0][0] = 1;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      int nx = nxt[j][s[i] - 'a'];
      dp[i][nx] = add(dp[i][nx], dp[i - 1][j]);
      if (s[i] == t[1] && j + 1 <= mx) {
        int nx = j + 1;
        dp[i][nx] = add(dp[i][nx], dp[i - 1][j]);
      } else {
        dp[i][j] = add(dp[i][j], dp[i - 1][j]);
      }
    }
    ans = add(ans, dp[i][m]);
  }
  cout << ans << endl;
  return 0;
}