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
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
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
const int maxn = 100000 + 5;

int tot, dfn[maxn << 1], ord[maxn << 1];
namespace hld {
  const int maxn = ::maxn << 1;
  struct edge { int to, nxt; } g[maxn];
  int head[maxn], ecnt = 0;
  void add(int x, int y) {
    g[++ecnt] = { y, head[x] }; head[x] = ecnt;
  }

  int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
  void dfs(int p, int d, int old) {
    dfn[p] = ++tot; ord[tot] = p;
    dep[p] = d; fa[p] = old; siz[p] = 1;
    int m = -1;
    for (int i = head[p]; i; i = g[i].nxt) {
      int v = g[i].to;
      if (v == fa[p]) continue;
      dfs(v, d + 1, p);
      siz[p] += siz[v];
      if (siz[v] > m) son[p] = v, m = siz[v];
    }
  }
  void dfs(int p, int tp) {
    top[p] = tp;
    if (!son[p]) return;
    dfs(son[p], tp);
    for (int i = head[p]; i; i = g[i].nxt) {
      int v = g[i].to;
      if (v == fa[p] || v == son[p]) continue;
      dfs(v, v);
    }
  }

  void build(int rt = 1) {
    ms(son, 0); dfs(rt, rt, 0); dfs(rt, rt);
  }

  int qlca(int x, int y) {
    while (top[x] != top[y]) {
      if (dep[top[x]] < dep[top[y]]) swap(x, y);
      x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    return x;
  }
}

vector<int> edge[maxn << 1];

struct sam {
  int sz, last, cnt[maxn << 1];
  int len[maxn << 1], link[maxn << 1], ch[maxn << 1][26];
  void clear() {
    for (int i = 1; i <= sz; i++) {
      len[i] = link[i] = cnt[i] = 0;
      ms(ch[i], 0);
    }
    sz = last = 1;
  }
  sam() {
    clear();
  }
  int insert(int c) {
    int cur = ++sz, p = last;
    len[cur] = len[last] + 1;
    cnt[cur] = 1;
    for (; p && !ch[p][c]; p = link[p]) ch[p][c] = cur;
    if (!p) link[cur] = 1;
    else {
      int q = ch[p][c];
      if (len[p] + 1 == len[q]) link[cur] = q;
      else {
        int nq = ++sz;
        len[nq] = len[p] + 1;
        link[nq] = link[q];
        link[q] = link[cur] = nq;
        memcpy(ch[nq], ch[q], sizeof ch[q]);
        for (; ch[p][c] == q; p = link[p]) ch[p][c] = nq;
      }
    }
    return last = cur;
  }
  void build(int tp) {
    if (tp == 0) {
      for (int i = 1; i <= sz; i++) {
        len[i]++;
        edge[link[i]].push_back(i);
      }
    } else {
      for (int i = 1; i <= sz; i++) {
        len[i]++;
        hld::add(link[i], i);
      }
      hld::build();
    }
  }
} ta, tb;

int n; ll ans;
char s[maxn];

int prepos[maxn], sufpos[maxn];

set<int> bag[maxn << 1];
ll val[maxn << 1];

void add(int u, int p) { // p: dfs order
  auto it = bag[u].lower_bound(p);
  int node = -1, d = hld::dep[ord[p]];
  if (it != bag[u].end()) {
    node = hld::qlca(ord[p], ord[*it]);
  }
  if (it != bag[u].begin()) {
    it--;
    int y = hld::qlca(ord[p], ord[*it]);
    if (node == -1 || abs(hld::dep[node] - d) > abs(hld::dep[y] - d)) node = y;
  }
  val[u] += tb.len[ord[p]];
  if (node != -1) val[u] -= tb.len[node];
  bag[u].insert(p);
}

void dfs(int u) {
  for (int v: edge[u]) {
    dfs(v);
    if (bag[v].size() > bag[u].size()) {
      swap(bag[u], bag[v]);
      val[u] = val[v];
    }
    for (auto& x: bag[v]) add(u, x);
  }
  ans += (val[u] + 1) * (ta.len[u] - ta.len[ta.link[u]]);
}

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  prepos[0] = sufpos[n + 1] = 1;
  for (int i = 1; i <= n; i++) {
    prepos[i] = ta.insert(s[i] - 'a');
  }
  for (int i = n; i >= 1; i--) {
    sufpos[i] = tb.insert(s[i] - 'a');
  }
  ta.build(0); tb.build(1);
  for (int i = 0; i < n; i++) {
    add(prepos[i], dfn[sufpos[i + 2]]);
  }
  dfs(1);
  cout << ans << endl;
  return 0;
}