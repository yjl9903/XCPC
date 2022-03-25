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
const int maxn = 2000 + 5;

int dis[150][10];
const vector<int> code = {
  119, 18, 93, 91, 58, 107, 111, 82, 127, 123
};

int n, k, a[maxn], dp[maxn][maxn];
char s[10];

int main() {
  for (int i = 0; i < 128; i++) {
    for (int j = 0; j < 10; j++) {
      if ((i | code[j]) == code[j]) {
        dis[i][j] = __builtin_popcount(code[j]) - __builtin_popcount(i);
      } else {
        dis[i][j] = -1;
      }
    }
  }
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s);
    int tot = 0;
    for (int j = 0; j < 7; j++) {
      tot = tot << 1 | (s[j] - '0');
    }
    a[i] = tot;
  }
  dp[n + 1][0] = true;
  for (int i = n; i >= 1; i--) {
    for (int j = 0; j < 10; j++) {
      if (dis[a[i]][j] == -1) continue;
      int d = dis[a[i]][j];
      for (int j = d; j <= k; j++) {
        dp[i][j] |= dp[i + 1][j - d];
      }
    }
  }
  string ans;
  for (int i = 1; i <= n; i++) {
    for (int j = 9; j >= 0; j--) {
      if (dis[a[i]][j] == -1) continue;
      int d = dis[a[i]][j];
      if (k < d) continue;
      if (dp[i + 1][k - d]) {
        k -= d;
        ans += j + '0';
        break;
      }
    }
  }
  if ((int)ans.length() < n) {
    puts("-1");
  } else {
    puts(ans.c_str());
  }
  return 0;
}