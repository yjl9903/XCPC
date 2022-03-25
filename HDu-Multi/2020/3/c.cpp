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
  int siz = 0, a[L];

  Info() {
    ms(a, 0);
  }

  int& operator [] (int i) { return a[i]; }
  const int& operator [] (int i) const { return a[i]; }

  void clear() {
    siz = 0;
    ms(a, 0);
  }

  Info operator + (const Info& rhs) const {
    Info r;
    r.siz = siz + rhs.siz;
    for (int i = 0; i < L; i++) {
      r[i] = a[i] + rhs[i];
    }
    return r;
  }

  void operator += (const Info& rhs) {
    siz += rhs.siz;
    for (int i = 0; i < L; i++) {
      a[i] += rhs[i];
    }
  }
  void operator -= (const Info& rhs) {
    siz -= rhs.siz;
    for (int i = 0; i < L; i++) {
      a[i] -= rhs[i];
    }
  }

  void add(int x, int v = 1) {
    siz += v;
    for (int i = 0; i < L; i++) {
      if (x >> i & 1) {
        a[i] += v;
      }
    }
  }
} all[maxn];
int allCnt[maxn];

namespace HLD {
  int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
  int dfn[maxn], rdfn[maxn], tot = 0;

  Info a[maxn * 40];
  int poolSz, root[maxn], ls[maxn * 40], rs[maxn * 40];
  int node() {
    int u = ++poolSz;
    ls[u] = rs[u] = 0;
    a[u].clear();
    return u;
  }
  void update(int i, int x, int v, int l, int r, int& rt) {
    if (!rt) rt = node();
    a[rt].add(x, v);
    if (l == r) return ;
    int m = (l + r) / 2;
    if (i <= m) {
      update(i, x, v, l, m, ls[rt]);
    } else {
      update(i, x, v, m + 1, r, rs[rt]);
    }
  }
  Info query(int L, int R, int l, int r, int rt) {
    if (!rt) return Info();
    if (L <= l && r <= R) return a[rt];
    int m = (l + r) / 2;
    if (R <= m) {
      return query(L, R, l, m, ls[rt]);
    } else if (L > m) {
      return query(L, R, m + 1, r, rs[rt]);
    } else {
      return query(L, R, l, m, ls[rt]) + query(L, R, m + 1, r, rs[rt]);
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

  Info qpath(int rt, int x, int y) {
    Info ans;
    while (top[x] != top[y]) {
      if (dep[top[x]] < dep[top[y]]) swap(x, y);
      ans += query(dfn[top[x]], dfn[x], 1, n, rt);
      x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    ans += query(dfn[x], dfn[y], 1, n, rt);
    return ans;
  }
  Info qson(int rt, int x) {
    return query(dfn[x], dfn[x] + siz[x] - 1, 1, n, rt);
  }

  ll query(int u, int v, int c) {
    Info sum = all[c];
    if (u != 1) {
      sum -= qpath(root[c], fa[u], 1);
    }
    sum -= qson(root[c], u);
    ll ans = 0;
    for (int i = 0; i < L; i++) {
      if (v >> i & 1) {
        ans += 1ll * (sum.siz - sum[i]) * (1 << i);
      } else {
        ans += 1ll * sum[i] * (1 << i);
      }
    }
    return ans;
  }

  ll build() {
    tot = poolSz = 0;
    dfs(1, 0);
    dfs(1, 0, 1);
    for (int i = 1; i <= n; i++) {
      root[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
      allCnt[col[i]]++;
      all[col[i]].add(val[i], 1);
      update(dfn[i], val[i], 1, 1, n, root[col[i]]);
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
      ans += query(i, val[i], col[i]);
    }
    return ans / 2;
  }

  void uVal(int u, int v) {
    update(dfn[u], val[u], -1, 1, n, root[col[u]]);
    update(dfn[u], v, 1, 1, n, root[col[u]]);
  }
  void uCol(int u, int c) {
    update(dfn[u], val[u], -1, 1, n, root[col[u]]);
    update(dfn[u], val[u], 1, 1, n, root[c]);
  }
}

int main() {
  int T; read(T);
  while (T--) {
    read(n);
    for (int i = 1; i <= n; i++) {
      read(col[i]);
      edge[i].clear();
      all[i].clear();
      allCnt[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
      read(val[i]);
    }
    for (int i = 2, u, v; i <= n; i++) {
      read(u, v);
      edge[u].push_back(v);
      edge[v].push_back(u);
    }

    ll ans = HLD::build();
    printf("%lld\n", ans);
    
    read(q);
    while (q--) {
      int op, u, x;
      read(op, u, x);
      ans -= HLD::query(u, val[u], col[u]);
      if (op == 1) {
        all[col[u]].add(val[u], -1);
        HLD::uVal(u, x);
        val[u] = x;
        all[col[u]].add(val[u], 1);
      } else if (op == 2) {
        allCnt[col[u]]--;
        all[col[u]].add(val[u], -1);
        HLD::uCol(u, x);
        col[u] = x;
        all[col[u]].add(val[u], 1);
        allCnt[col[u]]++;
      }
      ans += HLD::query(u, val[u], col[u]);
      printf("%lld\n", ans);
    }
  }
  return 0;
}