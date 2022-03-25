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
const int maxn = 100 + 5;

int n, m;
ll G[maxn][maxn], G2[maxn][maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      G[i][j] = inf;
    }
    G[i][i] = 0;
  }
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    G[u][v] = min(G[u][v], 1ll * w);
    G[v][u] = G[u][v];
  }
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (G[i][k] + G[k][j] < G[i][j]) {
          G[i][j] = G[i][k] + G[k][j];
        }
      }
    }
  }
  ll ans = inf;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
          G2[i][j] = G[i][j];
        }
      }
      G2[i][j] = G2[j][i] = 0;
      auto release = [&](int k) {
        for (int i = 1; i <= n; i++) {
          for (int j = 1; j <= n; j++) {
            if (G2[i][k] + G2[k][j] < G2[i][j]) {
              G2[i][j] = G2[i][k] + G2[k][j];
            }
          }
        }
      };
      release(i); release(j);
      ll sum = 0;
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
          sum += G2[i][j];
        }
      }
      ans = min(ans, sum);
    }
  }
  printf("%lld\n", ans);
  return 0;
}