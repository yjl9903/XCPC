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

int n, k;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    int p1 = -1, p2 = -1;
    for (int i = 1; i < n; i++) {
      if (k > i) {
        k -= i;
      } else {
        p2 = n - i;
        p1 = n - k + 1;
        // dbg(p1, p2);
        break;
      }
    }
    for (int i = 1; i <= n; i++) {
      if (i == p1 || i == p2) {
        putchar('b');
      } else {
        putchar('a');
      }
    }
    puts("");
  }
  return 0;
}