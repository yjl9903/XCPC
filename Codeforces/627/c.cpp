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

int n;
char s[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    auto check = [&](int x) -> bool {
      int tot = x;
      for (int i = 1; i <= n; i++) {
        if (i > tot) {
          return false;
        }
        if (s[i] == 'R') {
          tot = i + x;
        }
      }
      return tot >= n + 1;
    };
    int ans = n + 1, l = 1, r = n + 1;
    while (l <= r) {
      int m = (l + r) / 2;
      if (check(m)) {
        ans = m; r = m - 1;
      } else {
        l = m + 1;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}