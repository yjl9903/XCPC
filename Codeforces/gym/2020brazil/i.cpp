#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
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

int n, f[maxn], g[maxn];
vector<int> edge[maxn];

void dfs(int u) {
  if (edge[u].empty()) {
    f[u] = g[u] = 1;
    return ;
  }
  for (int v: edge[u]) {
    dfs(v);
  }
  vector<int> pre(edge[u].size()), suf(edge[u].size());
  for (int i = 0; i < edge[u].size(); i++) {
    int v = edge[u][i];
    pre[i] = f[v];
    if (i > 0) {
      pre[i] = mul(pre[i], pre[i - 1]);
    }
  }
  for (int i = (int)edge[u].size() - 1; i >= 0; i--) {
    int v = edge[u][i];
    suf[i] = f[v];
    if (i + 1 < edge[u].size()) {
      suf[i] = mul(suf[i], suf[i + 1]);
    }
  }
  g[u] = 0;
  for (int i = 0; i < edge[u].size(); i++) {
    int v = edge[u][i];
    int cur = g[v];
    if (i > 0) {
      cur = mul(cur, pre[i - 1]);
    }
    if (i + 1 < edge[u].size()) {
      cur = mul(cur, suf[i + 1]);
    }
    g[u] = add(g[u], cur);
  }
  f[u] = add(pre.back(), g[u]);
}

int main() {
  scanf("%d", &n);
  for (int i = 2; i <= n; i++) {
    int fa;
    scanf("%d", &fa);
    edge[fa].push_back(i);
  }
  dfs(1);
  printf("%d\n", f[1]);
  return 0;
}