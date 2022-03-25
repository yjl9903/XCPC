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
const int maxn = 500 + 5;

int n, x, y, a[maxn][maxn];

int solve(int sx, int sy) {
  vector<int> vec;
  for (int dx = -3; dx <= 3; dx++) {
    for (int dy = -3; dy <= 3; dy++) {
      if (dx == 0 && dy == 0) continue;
      if (abs(dx) + abs(dy) > 3) continue;
      int x = sx + dx, y = sy + dy;
      if (x < 1 || x > n || y < 1 || y > n) continue;
      vec.push_back(a[x][y]);
    }
  }
  sort(begin(vec), end(vec), greater<int>());
  int ans = 0, food = 0, tot = a[sx][sy];
  for (int i = 0; i < 8; i++) {
    int nxt = 8 * (i + 1) * (i + 1);
    int need = (nxt - food + tot - 1) / tot;
    if (need < 1) need = 1;
    ans += need;
    food += need * tot;
    if (i < (int)vec.size()) {
      tot += vec[i];
    }
  }
  return ans;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &x, &y);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        scanf("%d", &a[i][j]);
      }
    }
    int ans = inf;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        int dis = abs(x - i) + abs(y - j);
        ans = min(ans, (dis + 1) / 2 + solve(i, j));
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}