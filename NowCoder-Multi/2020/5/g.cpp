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
#include <queue>
#ifdef XLor
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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
const int maxn = 20000 + 5;

template<class T>
struct MaxFlow {
  struct Edge {
    int from, to;
    T cap, flow;

    Edge() {}
    Edge(int u, int v, T c, T f): from(u), to(v), cap(c), flow(f) {}
  };

  int n, m, s, t;
  T flow;
  vector<Edge> edges;
  vector< vector<int> > G;
  vector<int> dep, cur;

  void init(int _n, int _s, int _t) {
    n = _n;
    s = _s;
    t = _t;
    flow = 0;
    G.assign(n + 1, vector<int>());
    dep.assign(n + 1, -1);
    cur.assign(n + 1, 0);
    edges.clear();
  }
  void adde(int from, int to, T cap) {
    // dbg(from, to);
    if (from == to) return ;
    edges.emplace_back(from, to, cap, 0);
    edges.emplace_back(to, from, 0, 0);
    m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
  }
  bool bfs() {
    fill(begin(dep), end(dep), -1);
    queue<int> q;
    q.push(s);
    dep[s] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int i = 0; i < G[u].size(); i++) {
        Edge& e = edges[G[u][i]];
        if (dep[e.to] == -1 && e.cap > e.flow) {
          q.push(e.to);
          dep[e.to] = dep[u] + 1;
        }
      }
    }
    return dep[t] != -1;
  }
  T dfs(int x, T a) {
    if (x == t || a == 0) return a;
    T flow = 0, f;
    for (int& i = cur[x]; i < G[x].size(); i++) { 
      Edge& e = edges[G[x][i]];
      if (dep[x] + 1 == dep[e.to] && (f = dfs(e.to, min(a, e.cap - e.flow))) > 0) {
        e.flow += f;
        edges[G[x][i] ^ 1].flow -= f;
        flow += f;
        a -= f;
        if (a == 0) break;
      }
    }
    return flow;
  }
  T get() {
    while (bfs()) {
      fill(begin(cur), end(cur), 0);
      flow += dfs(s, inf);
    }
    return flow;
  }
};

MaxFlow<int> f;

int n, tot, rdfn[maxn], dfn[maxn], dep[maxn], fa[maxn];
vector<int> edge[maxn], col[maxn];

namespace HLD {
  int siz[maxn], son[maxn], top[maxn];
  void dfs(int u, int f) {
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    son[u] = 0;
    int m = -1;
    for (auto& v: edge[u]) {
      if (v == f) continue;
      dfs(v, u);
      siz[u] += siz[v];
      if (siz[v] > m) son[u] = v, m = siz[v];
    }
  }
  void dfs(int u, int f, int tp) {
    dfn[u] = ++tot;
    rdfn[tot] = u;
    top[u] = tp;
    ::f.adde(u, dfn[u] + n, 1);
    if (son[u]) {
      dfs(son[u], u, tp);
      ::f.adde(dfn[u] + n, dfn[son[u]] + n, n);
    }
    for (auto& v: edge[u]) {
      if (v == f || v == son[u]) continue;
      dfs(v, u, v);
    }
  }
  void build() {
    tot = 0;
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
}
using HLD::qlca;

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  void build(int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      f.adde(rdfn[l], n + n + rt, 1);
      return ;
    }
    int m = (l + r) / 2;
    f.adde(n + n + (rt << 1), n + n + rt, m - l + 1);
    f.adde(n + n + (rt << 1 | 1), n + n + rt, r - m);
    build(lson); build(rson);
  }
  void update(int L, int R, int tag, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      f.adde(n + n + rt, tag, 1);
      return ;
    }
    int m = (l + r) / 2;
    if (L <= m) update(L, R, tag, lson);
    if (R > m) update(L, R, tag, rson);
  }
}

inline int getMex(int v) {
  return 1 + n * 6 + v;
}

namespace VT {
  int top, cur, stk[maxn], siz[maxn];
  // vector<int> edge[maxn];
  void clear(int u) {
    edge[u].clear();
    siz[u] = 0;
  }
  void build(vector<int>& vec) {
    sort(vec.begin(), vec.end(), [&](int a, int b) { return dfn[a] < dfn[b]; });
    stk[top = 1] = 1;
    clear(1);
    for (int x: vec) {
      if (x == 1) continue;
      int g = qlca(stk[top], x);
      if (g != stk[top]) {
        while (dfn[g] < dfn[stk[top - 1]]) {
          edge[stk[top - 1]].push_back(stk[top]);
          top--;
        }
        if (dfn[g] > dfn[stk[top - 1]]) {
          clear(g);
          edge[g].push_back(stk[top]);
          stk[top] = g;
        } else {
          edge[g].push_back(stk[top]);
          top--;
        }
      }
      clear(x);
      stk[++top] = x;
    }
    for (int i = 1; i < top; i++) {
      edge[stk[i]].push_back(stk[i + 1]);
    }
    for (int x: vec) siz[x] = 1;
  }

  void link(int u, int f, int tag) {
    while (dep[HLD::top[u]] > dep[f]) {
      ::f.adde(dfn[u] + n, tag, 1);
      u = fa[HLD::top[u]];
    }
    if (dep[f] < dfn[u]) {
      SegT::update(dfn[f] + 1, dfn[u], tag);
    }
  }
  void dfs(int u, int f) {
    for (int v: edge[u]) {
      dfs(v, u);
      if (cur * siz[v] <= n) {
        int tag = getMex(cur * siz[v]);
        link(v, u, tag);
      }
      siz[u] += siz[v];
    }
    if (u == 1 && cur * siz[u] <= n) {
      ::f.adde(1, getMex(cur * siz[u]), 1);
    }
  }
}

int main() {
  scanf("%d", &n);
  f.init(7 * n + 10, 7 * n + 9, 7 * n + 10);
  for (int i = 2; i <= n; i++) {
    scanf("%d", &fa[i]);
    edge[fa[i]].push_back(i);
  }
  for (int i = 1, x; i <= n; i++) {
    scanf("%d", &x);
    col[x].push_back(i);
    f.adde(f.s, i, 1);
    f.adde(i, getMex(0), 1);
  }

  HLD::build();
  SegT::build();

  for (int i = 1; i <= n; i++) {
    if (col[i].empty()) continue;
    VT::cur = i;
    VT::build(col[i]);
    VT::dfs(1, 0);
  }

  int l = 1, r = n, ans = -1;
  while (l <= r) {
    int m = (l + r) / 2;

    auto edges = f.edges;
    auto flow = f.flow;
    auto G = f.G;
    
    for (int i = l - 1; i < m; i++) {
      f.adde(getMex(i), f.t, 1);
    }

    if (f.get() == m) {
      ans = m;
      l = m + 1;
    } else {
      f.flow = flow;
      f.edges = edges;
      f.G = G;

      r = m - 1;
    }
  }
  printf("%d\n", ans);
  return 0;
}