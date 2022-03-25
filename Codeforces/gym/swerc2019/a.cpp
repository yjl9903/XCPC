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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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
const ll inf = 1ll << 40;
const int maxn = 1000 + 5;

int dis(PII a, PII b) {
  int dx = a.first - b.first;
  int dy = a.second - b.second;
  double len = sqrt(dx * dx + dy * dy);
  return (int)ceil(len);
}

PII s, t, a[maxn];
int n, B, T, c[maxn];
ll dp[maxn][101];

struct E {
  int v, l; ll c;
};
vector<E> edge[maxn];

int main() {
  scanf("%d%d%d%d%d", &s.first, &s.second, &t.first, &t.second, &B);
  scanf("%d%d", &c[0], &T);
  for (int i = 1; i <= T; i++) {
    scanf("%d", c + i);
  }
  scanf("%d", &n);
  for (int i = 2, k; i <= n + 1; i++) {
    scanf("%d%d%d", &a[i].first, &a[i].second, &k);
    for (int j = 0, v, m; j < k; j++) {
      scanf("%d%d", &v, &m);
      v += 2; m = c[m];
      edge[i].push_back({ v, 0, m });
      edge[v].push_back({ i, 0, m });
    }
  }
  for (int i = 2; i <= n + 1; i++) {
    for (auto& x: edge[i]) {
      x.l = dis(a[i], a[x.v]);
      x.c *= x.l;
    }
  }
  edge[1].push_back({ n + 2, dis(s, t), 1ll * dis(s, t) * c[0] });
  for (int i = 2; i <= n + 1; i++) {
    edge[1].push_back({ i, dis(s, a[i]), 1ll * dis(s, a[i]) * c[0] });
    edge[i].push_back({ n + 2, dis(t, a[i]), 1ll * dis(t, a[i]) * c[0] });
  }
  for (int i = 2; i <= n + 2; i++) {
    for (int j = 0; j <= B; j++) {
      dp[i][j] = inf;
    }
  }
  while (true) {
    bool flag = false;
    for (int i = 1; i <= n + 1; i++) {
      for (auto& x: edge[i]) {
        int v = x.v, len = x.l; ll c = x.c;
        // dbg(i, v, len, c);
        for (int j = 0; j + len <= B; j++) {
          if (dp[i][j] >= inf) continue;
          if (dp[v][j + len] > dp[i][j] + c) {
            // dbg(i, j, dp[i][j], c);
            dp[v][j + len] = dp[i][j] + c;
            flag = true;
          }
        }
      }
    }
    if (!flag) break;
  }
  ll ans = inf;
  // for (int j = 0; j <= B; j++) {
  //   dbg(j, dp[n + 2][j]);
  // }
  for (int j = 0; j <= B; j++) ans = min(ans, dp[n + 2][j]);
  if (ans >= inf) puts("-1");
  else cout << ans << endl;
  return 0;
}