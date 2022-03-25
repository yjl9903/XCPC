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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 1023694381;
const ll inf = 1ll << 60;
const int maxn = 500 + 5;

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

int n, m, k, a[maxn];
ll f[maxn][maxn];
vector<PII> g[maxn];

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    for (int j = 1; j <= n; j++) {
      f[i][j] = inf;
    }
  }
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    f[u][v] = f[v][u] = w;
  }

  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
      }
    }
  }

  auto push = [&](int i, int x, int y) {
    if (x > y) swap(x, y);
    g[i].emplace_back(x, y);
  };
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j < i; j++) {
        if (f[i][k] + f[k][j] == f[i][j]) {
          push(k, i, j);
        }
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i == j) continue;
      push(i, i, j);
    }
    sort(g[i].begin(), g[i].end());
    g[i].resize(unique(g[i].begin(), g[i].end()) - g[i].begin());
  }
  int S = 1ll * n * (n - 1) / 2 % mod;
  int ivS = inv(S);
  int ans = n;
  for (int i = 1; i <= n; i++) {
    if (!a[i]) {
      int sz = g[i].size();
      int p = sub(1, mul(sz, ivS));
      ans = sub(ans, qpow(p, k));
    }
  }
  printf("%d\n", ans);
  return 0;
}