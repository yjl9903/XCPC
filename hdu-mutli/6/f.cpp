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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
  return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}
inline int inv(int x) {
  return qpow(x, mod - 2);
}

int n, m, a[maxn], pre[maxn], vis[maxn], cnt[maxn][2], siz[maxn][2];
vector<PII> edge[maxn];

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      pre[i] = i;
      vis[i] = 0;
      cnt[i][0] = cnt[i][1] = 0;
      cnt[i][a[i]] = 1;
      edge[i].clear();
    }
    int ans = 0;
    for (int i = 1, len = 2; i <= m; i++, len = add(len, len)) {
      int u, v;
      scanf("%d%d", &u, &v);
      int x = find(u), y = find(v);
      if (x == y) continue;
      pre[x] = y;
      cnt[y][0] += cnt[x][0];
      cnt[y][1] += cnt[x][1];      
      edge[u].emplace_back(v, len);
      edge[v].emplace_back(u, len);
    }
    for (int i = 1; i <= n; i++) {
      if (vis[i]) continue;
      int sum[2] = { cnt[find(i)][0], cnt[find(i)][1] };
      function<void(int,int)> dfs = [&](int u, int f) {
        vis[u] = 1;
        siz[u][0] = siz[u][1] = 0;
        siz[u][a[u]] = 1;
        for (auto x: edge[u]) {
          int v = x.first;
          if (v == f) continue;
          dfs(v, u);
          ans = add(ans, mul(x.second, mul(siz[v][0], sum[1] - siz[v][1])));
          ans = add(ans, mul(x.second, mul(siz[v][1], sum[0] - siz[v][0])));
          siz[u][0] += siz[v][0];
          siz[u][1] += siz[v][1];
        }
      };
      dfs(i, 0);
    }
    printf("%d\n", ans);
  }
  return 0;
}