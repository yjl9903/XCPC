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
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, t, dst = -1, eu = -1, ev = -1;
vector<int> edge[maxn], stk;

namespace hld {
  int tot, dfn[maxn], siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
  void dfs(int u, int f) {
    dfn[u] = ++tot;
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
  void build() {
    tot = 0;
    dep[1] = 0;
    dfs(1, 0);
    dfs(1, 0, 1);
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
  int qfa(int f, int u) {
    return dfn[f] <= dfn[u] && dfn[u] + siz[u] - 1 <= dfn[f] + siz[f] - 1;
  }
}

void dfs(int u, int f) {
  stk.push_back(u);
  if (u == n) {
    if (t < stk.size()) {
      dst = stk[t];
      if (t + 1 < stk.size()) {
        eu = stk[t];
        ev = stk[t + 1];
      }
    } else {
      dst = n;
    }
  }
  for (int v: edge[u]) {
    if (v == f) continue;
    dfs(v, u);
  }
  stk.pop_back();
}

int main() {
  scanf("%d%d", &n, &t);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  dfs(1, 0);
  if (dst == n) {
    puts("0");
    return 0;
  }
  hld::build();
  int ans = 0;
  for (int i = 1; i < n; i++) {
    if (edge[i].size() == 1) {
      int g = hld::qlca(n, i);
      int len1 = hld::qdis(dst, i);
      int len2 = hld::qdis(n, i);
      if (hld::qfa(dst, g)) {
        int d1 = hld::qdis(dst, g);
        int d2 = hld::qdis(n, g);
        if (d2 <= d1 + d1) {
          ans = max(ans, (d1 + d2 + 2) / 3);
          continue;
        } else {
          len1 -= d1;
          len2 -= d1 + d1;
        }
      } else {
        assert(hld::qfa(g, dst));
      }
      if (len2 >= len1 + len1) {
        ans = max(ans, (len2 + 1) / 2);
      } else {
        ans = max(ans, len2 - len1);
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}