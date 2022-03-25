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
const int maxn = 200000 + 5;

char s[maxn];
int n, x, y, pre[maxn][3];

int main() {
  scanf("%s%d%d", s + 1, &x, &y);
  n = strlen(s + 1);
  for (int i = 1; i <= n; i++) {
    if (s[i] != '?') {
      pre[i][s[i] - '0']++;
    } else {
      pre[i][2]++;
    }
    pre[i][0] += pre[i - 1][0];
    pre[i][1] += pre[i - 1][1];
    pre[i][2] += pre[i - 1][2];
  }
  ll base = 0, cur = 0;
  int cnt0 = 0, cnt1 = 0;
  for (int i = 1, j = 0; i <= n; i++) {
    if (s[i] == '0') {
      cnt0++;
      base += 1ll * cnt1 * y;
    } else if (s[i] == '1') {
      cnt1++;
      base += 1ll * cnt0 * x;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (s[i] == '?') { // 0
      cur += 1ll * pre[i][1] * y + 1ll * (pre[n][1] - pre[i][1]) * x;
    }
  }
  ll ans = cur;
  for (int i = n; i >= 1; i--) {
    if (s[i] == '?') {
      cur -= 1ll * pre[i][1] * y + 1ll * (pre[n][1] - pre[i][1]) * x;
      cur += 1ll * pre[i][0] * x + 1ll * (pre[n][0] - pre[i][0]) * y;
      cur += 1ll * pre[i - 1][2] * x;
      cur -= 1ll * (pre[n][2] - pre[i][2]) * x;
      ans = min(ans, cur);
    }
  }
  for (int i = n; i >= 1; i--) {
    if (s[i] == '?') {
      cur -= 1ll * pre[i][0] * x + 1ll * (pre[n][0] - pre[i][0]) * y;
      cur += 1ll * pre[i][1] * y + 1ll * (pre[n][1] - pre[i][1]) * x;
      cur += 1ll * pre[i - 1][2] * y;
      cur -= 1ll * (pre[n][2] - pre[i][2]) * y;
      ans = min(ans, cur);
    }
  }
  printf("%lld\n", base + ans);
  return 0;
}