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
const int maxn = 600000 + 5;

namespace LCT {
  int fa[maxn], ch[maxn][2], rev[maxn], mp[maxn], w[maxn];

  void clear() {
    ms(fa, 0);
    ms(ch, 0);
    ms(rev, 0);
  }

  int nroot(int x) {
    return ch[fa[x]][0] == x || ch[fa[x]][1] == x;
  }
  int get(int x) {
    return ch[fa[x]][1] == x;
  }
  void pushup(int x) {
    if (!x) return ;
    mp[x] = x;
    if (w[mp[ch[x][0]]] < w[mp[x]]) mp[x] = mp[ch[x][0]];
    if (w[mp[ch[x][1]]] < w[mp[x]]) mp[x] = mp[ch[x][1]];
  }
  void pushrev(int x) {
    swap(ch[x][0], ch[x][1]);
    rev[x] ^= 1;
  }
  void pushdown(int x) {
    if (!rev[x]) return;
    if (ch[x][0]) pushrev(ch[x][0]);
    if (ch[x][1]) pushrev(ch[x][1]);
    rev[x] = 0;
  }
  void rot(int x) {
    int old = fa[x], oldf = fa[old], k = get(x), w = ch[x][k ^ 1];
    if (nroot(old)) ch[oldf][ch[oldf][1] == old] = x;
    ch[x][k ^ 1] = old; ch[old][k] = w;
    if (w) fa[w] = old;
    fa[old] = x; fa[x] = oldf;
    pushup(old);
  }
  int st[maxn];
  void splay(int x) {
    int y = x, t = 0;
    st[++t] = y;
    while (nroot(y)) st[++t] = fa[y], y = fa[y];
    while (t) pushdown(st[t--]);
    while (nroot(x)) {
      y = fa[x];
      if (nroot(y)) rot(get(x) == get(y) ? y : x);
      rot(x);
    }
    pushup(x);
  }
  void access(int x) {
    for (int y = 0; x; y = x, x = fa[x])
      splay(x), ch[x][1] = y, pushup(x);
  }
  void make(int x) {
    access(x); splay(x); pushrev(x);
  }
  int findroot(int x) {
    access(x); splay(x);
    while (ch[x][0]) pushdown(x), x = ch[x][0];
    return x;
  }
  void split(int x, int y) {
    make(x);
    access(y);
    splay(y);
  }
  int link(int x, int y) {
    make(x);
    fa[x] = y;
    return true;
  }
  int cut(int x, int y) {
    make(x);
    access(y);
    splay(y);
    fa[x] = ch[y][0] = 0;
    pushup(y);
    return true;
  }
  int query(int x, int y) {
    split(x, y);
    return w[mp[y]];
  }
}

int n, m, q;
bool ans[maxn][2];

PII egs[maxn];
vector<PII> qry[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    LCT::clear();
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i <= n; i++) {
      LCT::w[i] = inf;
    }
    for (int i = 1; i <= m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      egs[i] = { u, v };
      qry[i].clear();
      LCT::w[i + n] = i;
    }
    for (int i = 1; i <= q; i++) {
      int L, R;
      scanf("%d%d", &L, &R);
      ans[i][0] = ans[i][1] = 0;
      {
        int k1 = L % m + 1;
        int k2 = R % m + 1;
        if (k1 > k2) swap(k1, k2);
        qry[k2].emplace_back(k1, i);
      }
      {
        int k1 = (L ^ 1) % m + 1;
        int k2 = (R ^ 1) % m + 1;
        if (k1 > k2) swap(k1, k2);
        qry[k2].emplace_back(k1, -i);
      }
    }
    
    int Le = -1;
    for (int R = 1; R <= m; R++) {
      int u = egs[R].first, v = egs[R].second;
      assert(u != v);
      if (LCT::findroot(u) == LCT::findroot(v)) {
        int eid = LCT::query(u, v);
        assert(1 <= eid && eid <= m);
        Le = max(Le, eid);

        LCT::cut(egs[eid].first, eid + n);
        LCT::cut(eid + n, egs[eid].second);

        LCT::link(u, R + n);
        LCT::link(R + n, v);
      } else {
        LCT::link(u, R + n);
        LCT::link(R + n, v);
      }
      dbg(Le, R);
      for (auto& q: qry[R]) {
        if (q.first <= Le) {
          int id = q.second;
          if (id > 0) {
            ans[id][0] = true;
          } else {
            ans[-id][1] = true;
          }
        }
      }
    }
    
    int last = 0;
    for (int i = 1; i <= q; i++) {
      last = ans[i][last];
      puts(last ? "Yes" : "No");
    }
  }
  return 0;
}