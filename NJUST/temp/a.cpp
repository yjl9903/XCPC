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
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, q;
vector<int> edge[maxn];

namespace hld{
  struct Info {
    int cnt, dep, pos;
    Info operator+(const Info& b) const {
      if (cnt > b.cnt) {
        return *this;
      } else if (cnt < b.cnt) {
        return b;
      } else {
        if (dep >= b.dep) {
          return *this;
        } else {
          return b;
        }
      }
    }
  } val[maxn << 2];

  int rid[maxn], laz[maxn << 2];
  int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn], id[maxn], cnt = 0;

  void pushup(int rt) {
    val[rt] = val[rt << 1] + val[rt << 1 | 1];
  }
  void pushdown(int rt, int ln, int rn) {
    if (!laz[rt]) return;
    int t = laz[rt];
    val[rt << 1].cnt += t;
    val[rt << 1 | 1].cnt += t;
    laz[rt << 1] += t;
    laz[rt << 1 | 1] += t;
    laz[rt] = 0;
  }
  void build(int l, int r, int rt) {
    laz[rt] = 0;
    if (l == r) {
      int u = rid[l];
      val[rt] = { 0, dep[u], u };
      return;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
  }
  void update(int L, int R, int x, int l, int r, int rt) {
    if (L <= l && r <= R) {
      laz[rt] += x;
      val[rt].cnt += x;
      return;
    }
    int m = (l + r) >> 1; pushdown(rt, m - l + 1, r - m);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
  }

  void dfs(int u, int d, int old) {
    son[u] = 0;
    dep[u] = d;
    fa[u] = old;
    siz[u] = 1;
    int m = -1;
    for (int v: edge[u]) {
      if (v == fa[u]) continue;
      dfs(v, d + 1, u);
      siz[u] += siz[v];
      if (siz[v] > m) son[u] = v, m = siz[v];
    }
  }
  void dfs(int u, int tp) {
    id[u] = ++cnt; rid[cnt] = u; top[u] = tp;
    if (!son[u]) return;
    dfs(son[u], tp);
    for (int v: edge[u]) {
      if (v == fa[u] || v == son[u]) continue;
      dfs(v, v);
    }
  }
  void init() {
    cnt = 0; dfs(1, 1, 0); dfs(1, 1); build(1, n, 1);
  }

  void upath(int x, int y, int k) {
    while (top[x] != top[y]) {
      if (dep[top[x]] < dep[top[y]]) swap(x, y);
      update(id[top[x]], id[x], k, 1, n, 1);
      x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    update(id[x], id[y], k, 1, n, 1);
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
    }
    for (int i = 2, u, v; i <= n; i++) {
      scanf("%d%d", &u, &v);
      u++; v++;
      edge[u].push_back(v);
      edge[v].push_back(u);
    }
    hld::init();
    scanf("%d", &q);
    int cnt = 0;
    while (q--) {
      char op[3]; int x;
      scanf("%s%d", op, &x);
      x++;
      if (op[0] == '+') {
        cnt++;
        hld::upath(1, x, 1);
      } else if (op[0] == '-') {
        cnt--;
        hld::upath(1, x, -1);
      }
      if (cnt == 0) {
        puts("-1");
      } else {
        printf("%d\n", hld::val[1].pos - 1);
      }
    }
  }
  return 0;
}