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


const int sz = 350;

int n, m, a[maxn], ans1[maxn], ans2[maxn];
vector<int> edge[maxn], Bag[maxn], que[maxn];

struct BIT {
  int a[maxn];
  void update(int i, int x) {
    for (; i <= n; i += i & -i) a[i] += x;
  }
  int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
  }
} bit;

int dfn[maxn], isT[maxn], tot;
int stk[maxn], tp, bcnt, bel[maxn];
int dep[maxn], fa[maxn], siz[maxn], son[maxn], top[maxn];
void dfs(int u, int f) {
  dfn[u] = ++tot; son[u] = 0;
  siz[u] = 1; dep[u] = dep[f] + 1; fa[u] = f;
  int m = -1, bot = tp;
  for (int& v: edge[u]) {
    if (v == f) continue;
    dfs(v, u);
    siz[u] += siz[v];
    if (siz[v] > m) m = siz[v], son[u] = v;
    if (tp - bot >= sz) {
      bcnt++;
      while (tp != bot) {
        bel[stk[tp--]] = bcnt;
      }
    }
  }
  stk[++tp] = u;
}
void dfs(int u, int f, int tp) {
  top[u] = tp;
  if (!son[u]) return ;
  dfs(son[u], u, tp);
  for (int& v: edge[u]) {
    if (v == f || v == son[u]) continue;
    dfs(v, u, v);
  }
}
int qlca(int u, int v) {
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) swap(u, v);
    u = fa[top[u]];
  }
  return dep[u] < dep[v] ? u : v;
}
void init() {
  tot = tp = bcnt = 0;
  dfs(1, 0);
  while (tp) bel[stk[tp--]] = bcnt;
  dfs(1, 0, 1);
}

struct Que {
  int u, v, w, id;
  bool operator< (const Que& b) const {
    if (bel[u] == bel[b.u]) return dfn[v] < dfn[b.v];
    return bel[u] < bel[b.u];
  }
} q[maxn];

int vis[maxn], bag[maxn], res;
void add(int x) {
  bag[x]++; if (bag[x] == 1) res++;
}
void del(int x) {
  bag[x]--; if (bag[x] == 0) res--;
}
void update(int u) {
  if (!vis[u]) {
    add(a[u]);
  } else {
    del(a[u]);
  }
  vis[u] ^= 1;
}
void move(int u, int v) {
  int g = qlca(u, v);
  for (int tot = u; tot != g; tot = fa[tot]) {
    update(tot);
  }
  for (int tot = v; tot != g; tot = fa[tot]) {
    update(tot);
  }
}

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    res = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      Bag[a[i]].push_back(i);
      edge[i].clear();
      vis[i] = 0;
    }
    for (int i = 2, u, v; i <= n; i++) {
      scanf("%d%d", &u, &v);
      edge[u].push_back(v);
      edge[v].push_back(u);
    }
    init();
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
      scanf("%d%d%d", &q[i].u, &q[i].v, &q[i].w);
      q[i].id = i;
      que[q[i].w].push_back(i);
    }

    for (int i = 1; i < maxn; i++) {
      bag[i] = 0;
      if (que[i].empty()) continue;
      for (int j = i; j < maxn; j += i) {
        for (int x: Bag[j]) {
          isT[x] = true;
          bit.update(dfn[x], 1);
          bit.update(dfn[x] + siz[x], -1);
        }
      }
      for (int id: que[i]) {
        int i = id;
        ans2[q[i].id] = bit.query(dfn[q[i].u]) + bit.query(dfn[q[i].v]);
        int g = qlca(q[i].u, q[i].v);
        ans2[q[i].id] -= 2 * bit.query(dfn[g]);
        ans2[q[i].id] += isT[g];
      }
      que[i].clear();
      for (int j = i; j < maxn; j += i) {
        for (int x: Bag[j]) {
          isT[x] = false;
          bit.update(dfn[x], -1);
          bit.update(dfn[x] + siz[x], 1);
        }
      }
    }
    
    sort(q + 1, q + 1 + m);
    int u = 1, v = 1;
    for (int i = 1; i <= m; i++) {
      move(u, q[i].u);
      move(v, q[i].v);
      u = q[i].u; v = q[i].v;
      int g = qlca(u, v);
      update(g);
      ans1[q[i].id] = res;
      update(g);
    }

    printf("Case #%d:\n", ++kase);
    for (int i = 1; i <= m; i++) {
      printf("%d\n", ans1[i] ^ ans2[i]);
    }
    for (int i = 1; i <= n; i++) {
      Bag[a[i]].clear();
    }
  }
  return 0;
}