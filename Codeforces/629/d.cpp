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
#include <queue>
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

int n, a[maxn], ans[maxn];

bool check() {
  bool flag = true; a[0] = a[n]; ans[0] = ans[n];
  for (int i = 1; i <= n; i++) {
    if (a[i] == a[i - 1] || ans[i] != ans[i - 1]) {
    } else {
      flag = false; break;
    }
  }
  return flag;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    if (*max_element(a + 1, a + 1 + n) == *min_element(a + 1, a + 1 + n)) {
      puts("1");
      for (int i = 1; i <= n; i++) {
        printf("1%c", i == n ? '\n' : ' ');
      }
      continue;
    }
    if (n % 2 == 0 || a[1] == a[n]) {
      puts("2");
      for (int i = 1; i <= n; i++) printf("%d%c", (i + 1) % 2 + 1, i == n ? '\n' : ' ');
      continue;
    } else {
      int pos = -1;
      for (int i = 1; i < n; i++) if (a[i] == a[i + 1]) {
        pos = i; break;
      }
      if (pos == -1) {
        puts("3");
        for (int i = 1; i < n; i++) printf("%d ", (i + 1) % 2 + 1);
        puts("3");
      } else {
        puts("2");
        for (int i = 1; i <= pos; i++) {
          printf("%d%c", (i + 1) % 2 + 1, i == n ? '\n' : ' ');
        }
        for (int i = pos + 1; i <= n; i++) {
          printf("%d%c", i % 2 + 1, i == n ? '\n' : ' ');
        }
      }
    }
  }
  return 0;
}