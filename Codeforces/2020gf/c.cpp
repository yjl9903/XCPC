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

int n, L, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &L);
    a[n + 1] = L;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    int px = 0, py = n + 1;
    int vx = 1, vy = 1;
    double ans = 0, lx = 0, ly = L;
    while (true) {
      if (px + 1 == py) {
        ans += (ly - lx) / (vx + vy);
        break;
      } else {
        double dx = (a[px + 1] - lx) / vx;
        double dy = (ly - a[py - 1]) / vy;
        if (dx < dy) {
          ans += dx;
          lx = a[px + 1];
          ly -= vy * dx;
          px++;
          vx++;
        } else {
          ans += dy;
          lx += vx * dy;
          ly = a[py - 1];
          py--;
          vy++;
        }
      }
    }
    printf("%.8lf\n", ans);
  }
  return 0;
}