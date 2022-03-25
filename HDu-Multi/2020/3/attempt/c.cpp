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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

namespace FastIO {
  const int SIZE = (1 << 21) + 1;
  char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
  // getchar
  #define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
  // print the remaining part
  inline void flush() {
    fwrite (obuf, 1, oS - obuf, stdout);
    oS = obuf;
  }
  // putchar
  inline void putc(char x) {
    *oS++ = x;
    if (oS == oT) flush ();
  }
  template<typename A>
  inline bool read(A &x) {
    for (f = 1, c = gc(); c < '0' || c > '9'; c = gc())
      if (c == '-') f = -1;
      else if (c == EOF) return 0;
    for (x = 0; c <= '9' && c >= '0'; c = gc())
      x = x * 10 + (c & 15);
    x *= f;
    return 1;
  }
  inline bool read(char &x) {
    while ((x = gc()) == ' '|| x == '\n' || x == '\r');
    return x!=EOF;
  }
  inline bool read(char *x) {
    while ((*x = gc()) =='\n' || *x == ' '|| *x == '\r');
    if (*x == EOF)return 0;
    while (!(*x == '\n'|| *x == ' ' || *x == '\r' || *x == EOF)) *(++x) = gc();
    *x = 0;
    return 1;
  }
  template<typename A, typename ...B>
  inline bool read(A& x, B&...y) {
    return read(x) && read(y...);
  }
  template<typename A>
  inline bool write (A x) {
    if (!x) putc ('0');
    if (x < 0) putc ('-'), x = -x;
    while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
    while (qr) putc (qu[qr --]);
    return 0;
  }
  inline bool write(char x) {
    putc(x);
    return 0;
  }
  inline bool write(const char *x) {
    while (*x) { putc(*x); ++x; }
    return 0;
  }
  inline bool write(char *x) {
    while (*x) { putc(*x); ++x; }
    return 0;
  }
  template<typename A, typename ...B>
  inline bool write(A x, B...y){
    return write(x) || write(y...);
  }
  //no need to call flush at the end manually!
  struct Flusher_ { ~Flusher_() { flush(); } } io_flusher_;
}
using FastIO :: read;
using FastIO :: putc;
using FastIO :: write;

int n, q, col[maxn], val[maxn];
vector<int> edge[maxn];

const int L = 20;

struct Info {
  int a[L];

  Info() {
    ms(a, 0);
  }

  int& operator [] (int i) { return a[i]; }
  const int& operator [] (int i) const { return a[i]; }

  void set(int x) {
    for (int i = 0; i < L; i++) {
      if (x >> i & 1) {
        a[i] = 1;
      } else {
        a[i] = 0;
      }
    }
  }

  Info operator + (const Info& rhs) const {
    Info r;
    for (int i = 0; i < L; i++) {
      r[i] = a[i] + rhs[i];
    }
    return r;
  }

  Info operator * (int k) const {
    Info r;
    for (int i = 0; i < L; i++) {
      r[i] = a[i] * k;
    }
    return r;
  }

  void add(int x, int v = 1) {
    for (int i = 0; i < L; i++) {
      if (x >> i & 1) {
        a[i] += v;
      }
    }
  }
};

namespace HLD {
  int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
  int dfn[maxn], rdfn[maxn], tot = 0;

  Info a[maxn * 40], tag[maxn * 2];
  int poolSz, root[maxn], ls[maxn * 40], rs[maxn * 40];
  int node() {
    int u = ++poolSz;
    ls[u] = rs[u] = 0;
    a[u].set(0);
    tag[u].set(0);
    return u;
  }
  void update(int L, int R, int x, int y, int l, int r, int& rt) {
    if (!rt) rt = node();
    a[rt].add(x, (R - L + 1) * y);
    if (L == l && r == R) {
      tag[rt].add(x, y);
      return ;
    }
    int m = (l + r) / 2;
    if (R <= m) {
      update(L, R, x, y, l, m, ls[rt]);
    } else if (L > m) {
      update(L, R, x, y, m + 1, r, rs[rt]);
    } else {
      update(L, m, x, y, l, m, ls[rt]);
      update(m + 1, R, x, y, m + 1, r, rs[rt]);
    }
  }
  Info query(int L, int R, Info ad, int l, int r, int rt) {
    if (!rt) return Info();
    if (L == l && r == R) return a[rt] + ad * (R - L + 1);
    int m = (l + r) / 2;
    if (R <= m) {
      return query(L, R, ad + tag[rt], l, m, ls[rt]);
    } else if (L > m) {
      return query(L, R, ad + tag[rt], m + 1, r, rs[rt]);
    } else {
      return query(L, m, ad + tag[rt], l, m, ls[rt]) + query(m + 1, R, ad + tag[rt], m + 1, r, rs[rt]);
    }
  }

  void dfs(int u, int f) {
    siz[u] = 1;
    dep[u] = dep[f] + 1;
    fa[u] = f;
    son[u] = 0;
    int m = -1;
    for (int v: edge[u]) {
      if (v == f) continue;
      dfs(v, u);
      siz[u] += siz[v];
      if (siz[v] > m) {
        m = siz[v];
        son[u] = v;
      }
    }
  }
  void dfs(int u, int f, int tp) {
    dfn[u] = ++tot;
    rdfn[tot] = u;
    top[u] = tp;
    if (son[u]) {
      dfs(son[u], u, tp);
    }
    for (int v: edge[u]) {
      if (v == f || v == son[u]) continue;
      dfs(v, u, v);
    }
  }
  void build() {
    tot = poolSz = 0;
    dfs(1, 0);
    dfs(1, 0, 1);
    for (int i = 1; i <= n; i++) {
      update(dfn[i], dfn[i], val[i], 1, 1, n, root[col[i]]);
    }
  }

  int qpath(int x, int y) {
    // int ans = 0;
    // while (top[x] != top[y]) {
    //   if (dep[top[x]] < dep[top[y]]) swap(x, y);
    //   ans = (ans + query(id[top[x]], id[x], 1, n, 1)) % p;
    //   x = fa[top[x]];
    // }
    // if (dep[x] > dep[y]) swap(x, y);
    // ans = (ans + query(id[x], id[y], 1, n, 1)) % p;
    // return ans;
  }
  int qson(int x) {
    // return query(id[x], id[x] + siz[x] - 1, 1, n, 1);
  }
  // void upath(int x, int y, int k) {
  //   k %= p;
  //   while (top[x] != top[y]) {
  //     if (dep[top[x]] < dep[top[y]]) swap(x, y);
  //     update(id[top[x]], id[x], k, 1, n, 1);
  //     x = fa[top[x]];
  //   }
  //   if (dep[x] > dep[y]) swap(x, y);
  //   update(id[x], id[y], k, 1, n, 1);
  // }
  // void uson(int x, int k) {
  //   update(id[x], id[x] + siz[x] - 1, k % p, 1, n, 1);
  // }
}

ll updateVal() {

}

ll updateCol() {

}

int main() {
  int T; read(T);
  while (T--) {
    read(n);
    for (int i = 1; i <= n; i++) {
      read(col[i]);
      edge[i].clear();
    }
    for (int i = 1; i <= n; i++) {
      read(val[i]);
    }
    for (int i = 2, u, v; i <= n; i++) {
      read(u, v);
      edge[u].push_back(v);
      edge[v].push_back(u);
    }
    HLD::build();
    
    read(q);
    while (q--) {
      int op, u, x;
      read(op, u, x);
      if (op == 1) {

      } else if (op == 2) {

      }
    }
  }
  return 0;
}