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
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, q, siz[maxn], fa[maxn], dep[maxn], dfn[maxn], tot;
vector<int> edge[maxn];

void dfs(int u, int f) {
  fa[u] = f;
  dep[u] = dep[f] + 1;
  dfn[u] = ++tot; siz[u] = 1;
  for (int v: edge[u]) {
    if (v == f) continue;
    dfs(v, u); siz[u] += siz[v];
  }
}
int check(int x, int y) {
  int xl = dfn[x], xr = dfn[x] + siz[x] - 1;
  int yl = dfn[y], yr = dfn[y] + siz[y] - 1;
  return xl <= yl && yr <= xr;
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  dfs(1, 0);
  while (q--) {
    int m; scanf("%d", &m);
    vector<PII> v;
    for (int i = 1, x; i <= m; i++) {
      scanf("%d", &x);
      if (x == 1) continue;
      x = fa[x];
      v.emplace_back(dep[x], x);
    }
    m = (int)v.size();
    sort(begin(v), end(v));
    bool flag = true;
    for (int i = 0; i + 1 < m; i++) {
      if (!check(v[i].second, v[i + 1].second)) {
        flag = false; break;
      }
    }
    puts(flag ? "YES" : "NO");
  }
  return 0;
}