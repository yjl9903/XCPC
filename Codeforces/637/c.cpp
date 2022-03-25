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
#include <deque>
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
using TLII = tuple<ll,int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxm = 10000 + 5;
const int maxt = 1000 + 5;

int n, m, a[maxm], G, R;
bool vis[maxm][maxt];
int dis[maxm][maxt];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d", a + i);
  }
  sort(a + 1, a + 1 + m);
  scanf("%d%d", &G, &R);
  for (int i = 1; i <= m; i++) {
    for (int j = 0; j <= G; j++) {
      dis[i][j] = inf;
    }
  }
  deque<tuple<int,int,int> > dq;
  dis[1][0] = 0;
  dq.emplace_back(0, 1, 0);
  while (!dq.empty()) {
    int d, u, t; tie(d, u, t) = dq.front(); dq.pop_front();
    if (vis[u][t]) continue;
    vis[u][t] = true;
    if (t == G && d + 1 < dis[u][0]) {
      dis[u][0] = d + 1;
      dq.emplace_back(d + 1, u, 0);
    }
    if (u > 1) {
      int st = t + a[u] - a[u - 1];
      if (st <= G && d < dis[u - 1][st]) {
        dis[u - 1][st] = d;
        dq.emplace_front(d, u - 1, st);
      }
    }
    if (u < m) {
      int st = t + a[u + 1] - a[u];
      if (st <= G && d < dis[u + 1][st]) {
        dis[u + 1][st] = d;
        dq.emplace_front(d, u + 1, st);
      }
    }
  }
  ll ans = 1e18;
  for (int i = 0; i <= G; i++) {
    if (dis[m][i] != inf) {
      ans = min(ans, 1ll * dis[m][i] * (G + R) + i);
    }
  }
  if (ans == (ll)1e18) puts("-1");
  else cout << ans << endl;
  return 0;
}