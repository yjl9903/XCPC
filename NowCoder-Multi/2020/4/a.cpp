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

namespace FastIO {
  const int SIZE = (1 << 21) + 1;
  char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[70];
  int f, qr;
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

int n, fa[18][maxn], tot, dfn[maxn], rid[maxn], siz[maxn], dep[maxn];
int cost[maxn];

struct Edge { int to, nxt; } e[maxn];
int head[maxn], ecnt;
void adde(int u, int v) {
  e[++ecnt] = Edge { v, head[u] };
  head[u] = ecnt;
}

int getK(int u, int k) {
  for (int i = 17; i >= 0; i--) {
    if (k & (1 << i)) {
      u = fa[i][u];
      k -= 1 << i;
    }
  }
  if (u == 0) u = 1;
  return u;
}

void dfs(int u, int f) {
  dfn[u] = ++tot;
  rid[tot] = u;
  siz[u] = 1;
  dep[u] = dep[f] + 1;
  fa[0][u] = f;
  for (int i = 1; i < 18; i++) {
    fa[i][u] = fa[i - 1][fa[i - 1][u]];
  }
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].to;
    dfs(v, u);
    siz[u] += siz[v];
  }
}

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  struct Info {
    ll mx;
    int pos;
  } a[maxn << 2];

  ll tag[maxn << 2];
  void pushup(int rt) {
    if (a[rt << 1].mx > a[rt << 1 | 1].mx) {
      a[rt] = a[rt << 1];
    } else {
      a[rt] = a[rt << 1 | 1];
    }
  }

  void build(int l = 1, int r = n, int rt = 1) {
    tag[rt] = 0;
    if (l == r) {
      int u = rid[l];
      a[rt] = Info { dep[u], u };
      return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
    pushup(rt);
  }

  void pushdown(int rt) {
    if (!tag[rt]) return ;
    tag[rt << 1] += tag[rt];
    tag[rt << 1 | 1] += tag[rt];
    a[rt << 1].mx += tag[rt];
    a[rt << 1 | 1].mx += tag[rt];
    tag[rt] = 0;
  }

  void update(int L, int R, int op = -1, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      tag[rt] += n * op;
      a[rt].mx += n * op;
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt);
    if (L <= m) update(L, R, op, lson);
    if (R > m) update(L, R, op, rson);
    pushup(rt);
  }
};

int upds[maxn], cntUpd;

int main() {
  while (read(n)) {
    ecnt = 0;
    for (int i = 1; i <= n; i++) {
      head[i] = 0;
    }
    for (int i = 2, fa; i <= n; i++) {
      read(fa);
      adde(fa, i);
    }

    tot = 0;
    dfs(1, 0);
    SegT::build();
    
    for (int k = 0; k < n; k++) {
      // Length: k
      int sum = 0;
      cntUpd = 0;
      while (SegT::a[1].mx > 0) {
        int u = getK(SegT::a[1].pos, k);
        SegT::update(dfn[u], dfn[u] + siz[u] - 1);
        upds[cntUpd++] = u;
        sum++;
      }
      for (int i = 0; i < cntUpd; i++) {
        int u = upds[i];
        SegT::update(dfn[u], dfn[u] + siz[u] - 1, 1);
      }
      cost[k] = sum;
    }

    ll ans = 0;
    for (int i = 1; i < n; i++) {
      ans += 1ll * i * (cost[i - 1] - cost[i]);
    }
    // printf("%lld\n", ans);
    write(ans, '\n');
  }
  return 0;
}