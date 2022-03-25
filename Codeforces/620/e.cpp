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
const int maxn = 100000 + 5;

int n, q;
vector<int> edge[maxn];

namespace hld {
  int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
  void dfs(int u, int f) {
    dep[u] = dep[f] + 1; fa[u] = f; siz[u] = 1; son[u] = 0;
    int m = -1;
    for (auto& v: edge[u]) {
      if (v == f) continue;
      dfs(v, u);
      siz[u] += siz[v];
      if (siz[v] > m) son[u] = v, m = siz[v];
    }
  }
  void dfs(int u, int f, int tp) {
    top[u] = tp;
    if (!son[u]) return;
    dfs(son[u], u, tp); // !
    for (auto& v: edge[u]) {
      if (v == f || v == son[u]) continue; // !
      dfs(v, u, v);
    }
  }
  void build() {
    dfs(1, 0); dfs(1, 0, 1);
  }
  int qlca(int u, int v) {
    while (top[u] != top[v]){
      if (dep[top[u]] < dep[top[v]]) swap(u, v);
      u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
  }
  int qdis(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[qlca(u, v)];
  }
}
using hld::qdis;

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  hld::build();
  scanf("%d", &q);
  while (q--) {
    int x, y, a, b, k;
    scanf("%d%d%d%d%d", &x, &y, &a, &b, &k);
    auto check = [&](int d) {
      return d <= k && (k - d) % 2 == 0;
    };
    bool flag = check(qdis(a, b));
    if (!flag) flag = check(qdis(a, x) + qdis(y, b) + 1);
    if (!flag) flag = check(qdis(a, y) + qdis(x, b) + 1);
    puts(flag ? "YES" : "NO");
  }
  return 0;
}