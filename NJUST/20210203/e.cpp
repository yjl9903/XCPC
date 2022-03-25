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

int n, m, f[maxn], g[maxn];
bool vis[maxn];
vector<int> edge[maxn];

void dfs(int u) {
  if (vis[u]) return ;
  vis[u] = true;
  g[u] = 1;
  for (int v: edge[u]) {
    dfs(v);
    g[u] = add(g[u], g[v]);
    f[u] = add(f[u], f[v]);
    f[u] = add(f[u], g[v]);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
  }
  int fz = 0, fm = 0;
  for (int i = 1; i <= n; i++) {
    dfs(i);
    fz = add(fz, f[i]);
    fm = add(fm, g[i]);
  }
  int ans = mul(fz, inv(fm));
  printf("%d\n", ans);
  return 0;
}