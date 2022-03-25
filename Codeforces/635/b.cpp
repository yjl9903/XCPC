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
const ll inf = 1ll << 61;
const int maxn = 200000 + 5;

int n[3], a[3][maxn];
set<int> st[3];

ll cal(int x, int y, int z) {
  return 1ll * (x - y) * (x - y) + 1ll * (y - z) * (y - z) + 1ll * (x - z) * (x - z);
}

ll solve(int x, int y, int z) {
  ll ans = inf;
  for (int i = 1; i <= n[z]; i++) {
    auto it0 = st[x].upper_bound(a[z][i]);
    auto it1 = st[y].upper_bound(a[z][i]);
    for (int j = 0; j < 3; j++) {
      if (it0 == st[x].end()) {
        it0--; continue;
      }
      auto it = st[y].upper_bound(a[z][i]);
      for (int k = 0; k < 3; k++) {
        if (it == st[y].end()) {
          it--; continue;
        }
        ans = min(ans, cal(*it0, *it, a[z][i]));
        if (it == st[y].begin()) break;
        it--;
      }
      if (it0 == st[x].begin()) break;
      it0--;
    }
  }
  return ans;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n[0], &n[1], &n[2]);
    for (int i = 0; i < 3; i++) {
      st[i].clear();
      for (int j = 1; j <= n[i]; j++) {
        scanf("%d", &a[i][j]);
        st[i].insert(a[i][j]);
      }
    }
    ll ans = min(solve(0, 1, 2), min(solve(0, 2, 1), solve(1, 2, 0)));
    printf("%I64d\n", ans);
  }
  return 0;
}