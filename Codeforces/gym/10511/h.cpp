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
const ll inf = 1e15;
const int maxn = 200000 + 5;

struct Edge {
  int to, flow, cost; 
};
vector<Edge> edge[maxn];

int n, id[maxn];
ll cost[maxn], flow[maxn];
int dep[maxn], fa[maxn], siz[maxn], son[maxn], top[maxn];
int tot, rid[maxn], L[maxn], R[maxn];
void predfs(int u, int f) {
  siz[u] = 1;
  for (auto& x: edge[u]) {
    int v = x.to;
    if (v == f) continue;
    fa[v] = u;
    dep[v] = dep[u] + 1;
    cost[v] = cost[u] + x.cost;
    flow[v] = x.flow;
    predfs(v, u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}
void dfs(int u, int f, int tp) {
  L[u] = ++tot;
  rid[tot] = u;
  top[u] = tp;
  if (son[u]) {
    dfs(son[u], u, tp);
  }
  for (auto& x: edge[u]) {
    int v = x.to;
    if (v == f || v == son[u]) continue;
    dfs(v, u, v);
  }
  R[u] = tot;
}

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  long double a[maxn << 2], tag[maxn << 2];
  void build(int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      int u = rid[l];
      a[rt] = ::flow[u];
      return ;
    }
    int m = (l + r) / 2;
    build(lson);
    build(rson);
    a[rt] = min(a[rt << 1], a[rt << 1 | 1]);
  }

  void apply(int u, long double x) {
    a[u] += x;
    tag[u] += x;
  }
  void pushdown(int rt) {
    apply(rt << 1, tag[rt]);
    apply(rt << 1 | 1, tag[rt]);
    tag[rt] = 0;
  }

  void update(int L, int R, long double x, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      apply(rt, x);
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    a[rt] = min(a[rt << 1], a[rt << 1 | 1]);
  }

  long double query(int L, int R, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) return a[rt];
    int m = (l + r) / 2;
    pushdown(rt);
    if (R <= m) return query(L, R, lson);
    else if (L > m) return query(L, R, rson);
    else return min(query(L, R, lson), query(L, R, rson));
  }
}

long double qpath(int x, int y) {
  long double ans = inf;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    ans = min(ans, SegT::query(L[top[x]], L[x]));
    x = fa[top[x]];
  }
  if (dep[x] > dep[y]) swap(x, y);
  ans = min(ans, SegT::query(L[x], L[y]));
  return ans;
}
void upath(int x, int y, long double val) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    SegT::update(L[top[x]], L[x], val);
    x = fa[top[x]];
  }
  if (dep[x] > dep[y]) swap(x, y);
  SegT::update(L[x], L[y], val);
}

int main() {
  scanf("%d", &n);
  for (int i = 2; i <= n; i++) {
    int u, v, a, b;
    scanf("%d%d%d%d", &u, &v, &a, &b);
    edge[u].push_back({ v, a, b });
    edge[v].push_back({ u, a, b });
  }
  flow[1] = inf;
  predfs(1, 0);
  dfs(1, 0, 1);
  for (int i = 1; i <= n; i++) {
    id[i] = i;
    dbg(i, L[i], R[i]);
  }
  SegT::build();
  sort(id + 1, id + 1 + n, [&](int x, int y) {
    return cost[x] < cost[y];
  });
  long double ans = 0;
  long double sum = 0;
  for (int i = 1; i <= n; i++) {
    int u = id[i];
    if (son[u] != 0) continue;
    if (cost[u] < 0) {
      long double fl = qpath(1, u);
      dbg(fl);
      ans += fl;
      sum -= fl * cost[u];
      upath(1, u, -fl);
    } else {
      long double fl = qpath(1, u);
      if (cost[u] != 0) {
        fl = min(fl, sum / cost[u]);
      }
      ans += fl;
      sum -= fl * cost[u];
      upath(1, u, -fl);
    }
    dbg(ans, sum);
  }
  printf("%.15Lf\n", ans);
  return 0;
}