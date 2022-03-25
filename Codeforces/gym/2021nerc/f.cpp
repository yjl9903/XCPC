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

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    map<PII, int> mp0, mp1;
    for (int i = 1; i <= n; i++) {
      int x1, y1, x2, y2;
      scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
      int dx = x2 - x1;
      int dy = y2 - y1;
      int g = __gcd(abs(dx), abs(dy));
      dx /= g;
      dy /= g;
      // dbg(dx, dy);
      if (dx == 0) {
        if (dy > 0) mp0[{ dx, dy }]++;
        else mp1[{ dx, -dy }]++;
      } else if (dy == 0) {
        if (dx > 0) mp0[{ dx, dy }]++;
        else mp1[{ -dx, dy }]++;
      } else {
        if (dx > 0 && dy > 0) {
          mp0[{ dx, dy }]++;
        } else if (dx > 0 && dy < 0) {
          mp0[{ dx, dy }]++;
        } else if (dx < 0 && dy > 0) {
          mp1[{ -dx, -dy }]++;
        } else if (dx < 0 && dy < 0) {
          mp1[{ -dx, -dy }]++;
        }
      }
    }
    ll ans = 0;
    for (auto& x: mp0) {
      if (mp1.count(x.first)) {
        ans += 1ll * x.second * mp1[x.first];
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}