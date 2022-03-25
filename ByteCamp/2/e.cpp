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
const int maxn = 1000000 + 5;

int n, q, key[maxn];

int tot, dfn[maxn], dep[maxn], fa[20][maxn];
vector<int> edge[maxn];

void getdep(int u, int f) {
  fa[0][u] = f;
  for (int i = 1; i < 20; i++) {
    fa[i][u] = fa[i - 1][fa[i - 1][u]];
  }
  dfn[u] = ++tot;
  dep[u] = dep[f] + 1;
  for (int v: edge[u]) {
    if (v == f) continue;
    getdep(v, u);
  }
}
int qlca(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  int tmp = dep[x] - dep[y];
  for (int i = 0; tmp; i++, tmp >>= 1)
    if (tmp & 1) x = fa[i][x];
  if (x == y) return x;
  for (int i = 19; i >= 0; i--) {
    if (fa[i][x] != fa[i][y]) {
      x = fa[i][x]; y = fa[i][y];
    }
  }
  return fa[0][x];
}

namespace VT {
  const int rt = 1;
  int stk[maxn], top;
  void build(vector<int>& vec) {
    sort(vec.begin(), vec.end(), [&](int a, int b) { return dfn[a] < dfn[b]; });
    stk[top = 1] = rt; edge[rt].clear();
    for (int x: vec) {
      if (x == rt) continue;
      int g = qlca(stk[top], x);
      if (g != stk[top]) {
        while (dfn[g] < dfn[stk[top - 1]]) {
          edge[stk[top - 1]].push_back(stk[top]); top--;
        }
        if (dfn[g] > dfn[stk[top - 1]]) {
          edge[g].clear();
          edge[g].push_back(stk[top]);
          stk[top] = g;
        } else {
          edge[g].push_back(stk[top]); top--;
        }
      }
      edge[x].clear(); stk[++top] = x;
    }
    for (int i = 1; i < top; i++) {
      edge[stk[i]].push_back(stk[i + 1]);
    }
  }
}

int K, siz[maxn];
ll ans = 0;
void dfs(int u) {
  // dbg(u);
  siz[u] = key[u];
  for (int v: edge[u]) {
    dfs(v);
    if (u != 1) {
      ans += 1ll * (dep[v] - dep[u]);
    } else {
      if (key[u] || edge[u].size() > 1) {
        ans += 1ll * (dep[v] - dep[u]);
      }
    }
    siz[u] += siz[v];
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  getdep(1, 0);
  scanf("%d", &q);
  while (q--) {
    int x; scanf("%d", &K);
    vector<int> vec;
    for (int i = 1; i <= K; i++) {
      scanf("%d", &x); vec.push_back(x);
      key[x] = 1;
    }
    VT::build(vec); 
    ans = 0; dfs(1);
    printf("%lld\n", ans);
    for (int x: vec) {
      key[x] = 0;
    }
  }
  return 0;
}