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
const int mod = 998244353;
const ll inf = 1ll << 60;
const int maxn = 600 + 5;

int n, m, q;
ll f[maxn][maxn], L[maxn][maxn], mn[maxn][maxn];
int uu[maxn * maxn], vv[maxn * maxn], ww[maxn * maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      f[i][j] = inf;
      L[i][j] = inf;
      mn[i][j] = inf;
    }
    f[i][i] = 0;
  }
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    f[u][v] = f[v][u] = min(f[u][v], 1ll * w);
    uu[i] = u;
    vv[i] = v;
    ww[i] = w;
  }
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
      }
    }
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    int u, v, l;
    scanf("%d%d%d", &u, &v, &l);
    L[u][v] = L[v][u] = -1ll * l;
  }
  for (int x = 1; x <= n; x++) {
    for (int u = 1; u <= n; u++) {
      for (int v = 1; v <= n; v++) {
        mn[x][u] = min(mn[x][u], f[x][v] + L[u][v]);
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= m; i++) {
    int x = uu[i], y = vv[i], w = ww[i];
    for (int i = 1; i <= n; i++) {
      if (mn[x][i] <= -w - f[y][i]) {
        ans++;
        break;
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}