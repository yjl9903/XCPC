#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
const int maxn = 300000 + 5;

int n, k, rt, fa[maxn];
int bel[maxn], nxt[maxn], pre[maxn], deg[maxn];
vector<int> edge[maxn], G[maxn], bag[maxn];

namespace hld {
  int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
  void dfs(int u, int f) {
    fa[u] = f; siz[u] = 1; son[u] = 0;
    int m = -1;
    for (auto& v: edge[u]) {
      if (v == f) continue;
      dep[v] = dep[u] + 1;
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
  void build(int rt = 1) {
    dep[rt] = 0;
    dfs(rt, 0);
    dfs(rt, 0, rt);
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

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", fa + i);
    if (fa[i]) {
      edge[fa[i]].push_back(i);
      edge[i].push_back(fa[i]);
    } else {
      rt = i;
    }
  }
  hld::build(rt);
  for (int i = 1; i <= k; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    nxt[x] = y;
    pre[y] = x;
    int g = hld::qlca(x, y);
    if (g == y) {
      puts("0");
      return 0;
    }
  }
  int sz = 0;
  for (int i = 1; i <= n; i++) {
    if (nxt[i] && !pre[i]) {
      sz++;
      int u = i;
      do {
        bel[u] = i;
        bag[i].push_back(u);
        u = nxt[u];
      } while (u);
    } else if (!nxt[i] && !pre[i]) {
      sz++;
      bel[i] = i;
      bag[i].push_back(i);
    }
  }
  for (int i = 1; i <= n; i++) {
    if (fa[i]) {
      int u = bel[fa[i]];
      int v = bel[i];
      if (u != v) {
        G[u].push_back(v);
        deg[v]++;
      }
    }
  }
  vector<int> ord;
  for (int i = 1; i <= n; i++) {
    if (i == bel[i] && deg[i] == 0) {
      ord.push_back(i);
    }
  }
  for (int i = 0; i < ord.size(); i++) {
    int u = ord[i];
    for (int v: G[u]) {
      deg[v]--;
      if (deg[v] == 0) {
        ord.push_back(v);
      }
    }
  }
  if (ord.size() == sz) {
    for (int u: ord) {
      for (int x: bag[u]) {
        printf("%d ", x);
      }
    }
  } else {
    puts("0");
  }
  return 0;
}