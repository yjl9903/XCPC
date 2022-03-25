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
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, mx, rt;
vector<int> edge[maxn];

void predfs(int u, int f, int d) {
  if (d > mx) {
    mx = d; rt = u;
  }
  for (int v: edge[u]) {
    if (v == f) continue;
    predfs(v, u, d + 1);
  }
}

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
  void build(int rt) {
    dfs(rt, 0); dfs(rt, 0, rt);
  }
  int qlca(int u, int v) {
    while (top[u] != top[v]){
      if (dep[top[u]] < dep[top[v]]) swap(u, v);
      u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
  }
}
using hld::dep;

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  predfs(1, 0, 1);
  int da = rt;
  mx = rt = 0;
  predfs(da, 0, 1);
  int db = rt, ans = mx;
  hld::build(da);
  int dc = -1;
  for (int i = 1; i <= n; i++) {
    if (i == da || i == db) continue;
    int g = hld::qlca(db, i);
    if (mx + dep[i] - dep[g] >= ans) {
      ans = mx + dep[i] - dep[g];
      dc = i;
    }
  }
  printf("%d\n%d %d %d", ans - 1, da, db, dc);
  return 0;
}