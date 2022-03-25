#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

namespace FastIO {
  const int SIZE = (1 << 21) + 1;
  char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[100]; int f, qr;
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

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
  return 1ll * x * y % mod;
}

int n, m, cnt, inv[maxn];
vector<int> edge[maxn * 2];
vector<int> bcc[maxn];
vector<PII> isRing;

void ins(int u, int v) {
  if (u > v) swap(u, v);
  isRing.emplace_back(u, v);
}
bool qry(int u, int v) {
  if (u > v) swap(u, v);
  auto it = lower_bound(begin(isRing), end(isRing), PII { u, v });
  if (it == end(isRing)) {
    return true;
  } else {
    return *it != PII { u, v };
  }
}

namespace cactus {
  struct E {
    int to, nxt;
  } e[maxn * 4];
  int head[maxn], ecnt;
  void adde(int u, int v) {
    e[++ecnt] = { v, head[u] };
    head[u] = ecnt;
  }
  int tot, dfn[maxn], fa[maxn];
  bool ring[maxn];
  void clear(int n) {
    isRing.clear();
    cnt = ecnt = tot = 0;
    for (int i = 1; i <= n; i++) {
      head[i] = dfn[i] = 0;
      ring[i] = false;
      bcc[i].clear();
    }
  }
  void dfs(int u, int f) {
    dfn[u] = ++tot;
    int noF = true;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].to;
      if (v == f && noF) {
        noF = false;
        continue;
      }
      if (!dfn[v]) {
        fa[v] = u;
        ring[u] = false;
        dfs(v, u);
        if (!ring[u]) {
          edge[u].emplace_back(v);
          edge[v].emplace_back(u);
        }
      } else if (dfn[v] < dfn[u]) {
        cnt++;
        int rt = cnt + n;
        edge[rt].emplace_back(v);
        edge[v].emplace_back(rt);
        bcc[cnt].push_back(v);
        for (int x = u; x != v; x = fa[x]) {
          ring[x] = true;
          bcc[cnt].push_back(x);
          edge[rt].emplace_back(x);
          edge[x].emplace_back(rt);
          ins(x, fa[x]);
        }
        ins(u, v);
        ring[v] = true;
      }
    }
  }
  void build() {
    dfs(1, 0);
    sort(begin(isRing), end(isRing));
  }
}

int ans, siz[maxn * 2];
void dfs(int u, int f) {
  siz[u] = u <= n;
  for (int v: edge[u]) {
    if (v == f) continue;
    dfs(v, u);
    if (u <= n && v <= n && qry(u, v)) {
      ans = add(ans, mul(siz[v], n - siz[v]));
    }
    siz[u] += siz[v];
  }
  if (u > n) {
    vector<int>& vec = bcc[u - n];
    int len = vec.size();
    vector<int> siz(len, 0);
    siz[0] = n;
    for (int i = 1; i < len; i++) {
      int u = vec[i];
      siz[i] = ::siz[u];
      siz[0] -= siz[i];
    }
    assert(1 <= siz[0] && siz[0] <= n);

    int cur = 0;
    int xs = siz[0], s = siz[0], x2s = siz[0];
    for (int i = 1; i < len; i++) {
      cur = add(cur, mul(siz[i], sub(mul(xs, len), x2s)));

      int Nxs = add(xs, add(s, siz[i]));
      int Ns = add(s, siz[i]);
      int Nx2s = add(x2s, siz[i]);
      Nx2s = add(Nx2s, mul(2, xs));
      Nx2s = add(Nx2s, s);
      
      xs = Nxs;
      s = Ns;
      x2s = Nx2s;
    }
    ans = add(ans, mul(cur, inv[len]));
  }
}

int main() {
  inv[1] = 1;
  for (int i = 2; i < maxn; i++) {
    inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
  }
  int T;
  read(T);
  while (T--) {
    read(n, m);
    cactus::clear(n);
    for (int i = 1; i <= 2 * n; i++) {
      edge[i].clear();
    }
    for (int i = 1, u, v, w; i <= m; i++) {
      read(u, v);
      cactus::adde(u, v);
      cactus::adde(v, u);
    }
    cactus::build();
    ans = 0;
    dfs(1, 0);
    write(ans, '\n');
  }
  return 0;
}