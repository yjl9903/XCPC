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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, k, a[maxn];

namespace hld {
  struct edge { int to, nxt, w; } g[maxn];
  int head[maxn], tot = 0;
  void add(int x, int y, int w) {
    g[++tot] = {y, head[x], w}; head[x] = tot;
  }

  int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];

  void dfs(int p, int d, int old) {
    dep[p] = d; fa[p] = old; siz[p] = 1;
    int m = -1;
    for (int i = head[p]; i; i = g[i].nxt) {
      int v = g[i].to;
      if (v == fa[p]) continue;
      dfs(v, d + 1, p);
      siz[p] += siz[v];
      if (siz[v] > m) son[p] = v, m = siz[v];
    }
  }
  void dfs(int p, int tp) {
    top[p] = tp;
    if (!son[p]) return;
    dfs(son[p], tp);
    for (int i = head[p]; i; i = g[i].nxt) {
      int v = g[i].to;
      if (v == fa[p] || v == son[p]) continue;
      dfs(v, v);
    }
  }

  void init() {
    ms(son, 0); dfs(1, 1, 0); dfs(1, 1);
  }

  int qlca(int x, int y) {
    while (top[x] != top[y]) {
      if (dep[top[x]] < dep[top[y]]) swap(x, y);
      x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    return x;
  }
}

int check(int u, int v) {
  int g = hld::qlca(u, v);
  if (u == g) return false;
  if (v == g) return false;
  if (hld::dep[u] + hld::dep[v] - 2 * hld::dep[g] > k) return false;
  if (a[u] + a[v] != 2 * a[g]) return false;
  return true;
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 2, fa; i <= n; i++) {
    scanf("%d", &fa);
    hld::add(fa, i, 1);
  }
  hld::init();
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (check(i, j)) ans++;
    }
  }
  cout << ans << endl;
  return 0;
}