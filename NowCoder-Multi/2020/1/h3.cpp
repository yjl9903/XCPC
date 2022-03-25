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
#include <queue>
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

const int maxn = 400 + 5;

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

int n, m, q;
vector<ll> costs;

struct MCMF {
  struct E {
    int from, to, cap, v;
    E() {}
    E(int f, int t, int cap, int v) : from(f), to(t), cap(cap), v(v) {}
  };

  int n, m, s, t;
  vector<E> edges;
  vector<int> G[maxn];
  bool inq[maxn];
  int dis[maxn], pre[maxn], a[maxn];

  void init(int _n, int _s, int _t) {
    n = _n; s = _s; t = _t;
    for (int i = 0; i <= n; i++) {
      G[i].clear();
    }
    edges.clear();
    m = 0;
  }

  void add(int from, int to, int cap, int cost) {
    edges.emplace_back(from, to, cap, cost);
    edges.emplace_back(to, from, 0, -cost);
    G[from].push_back(m++);
    G[to].push_back(m++);
  }

  bool spfa() {
    for (int i = 0; i <= n; i++) {
      dis[i] = 1e9;
      pre[i] = -1;
      inq[i] = false;
    }
    dis[s] = 0, a[s] = 1e9, inq[s] = true;
    queue<int> Q; Q.push(s);
    while (!Q.empty()) {
      int u = Q.front(); Q.pop();
      inq[u] = false;
      for (int& idx: G[u]) {
        E& e = edges[idx];
        if (e.cap && dis[e.to] > dis[u] + e.v) {
          dis[e.to] = dis[u] + e.v;
          pre[e.to] = idx;
          a[e.to] = min(a[u], e.cap);
          if (!inq[e.to]) {
            inq[e.to] = true;
            Q.push(e.to);
          }
        }
      }
    }
    return pre[t] != -1;
  }

  int solve() {
    costs.clear();
    int flow = 0, cost = 0;
    while (spfa()) {
      flow += a[t];
      cost += a[t] * dis[t];

      assert(a[t] == 1);
      costs.push_back(cost);

      int u = t;
      while (u != s) {
        edges[pre[u]].cap -= a[t];
        edges[pre[u] ^ 1].cap += a[t];
        u = edges[pre[u]].from;
      }
    }
    return cost;
  }
} f;

using Frac = pair<__int128, __int128>; // first / second
Frac make(__int128 fz, __int128 fm) {
  if (fz == 0) {
    return Frac { 0, 1 };
  }
  ll g = __gcd(fz, fm);
  assert(fm > 0);
  return make_pair(fz / g, fm / g);
}
Frac add(Frac a, Frac b) {
  auto fz = a.first * b.second + b.first * a.second;
  auto fm = a.second * b.second;
  return make(fz, fm);
}
Frac sub(Frac a, Frac b) {
  auto fz = a.first * b.second - b.first * a.second;
  auto fm = a.second * b.second;
  return make(fz, fm);
}
Frac mul(Frac a, __int128 k) {
  return make(a.first * k, a.second);
}

int main() {
  while (read(n, m)) {
    f.init(n, 1, n);
    for (int i = 1, u, v, w; i <= m; i++) {
      read(u, v, w);
      f.add(u, v, 1, w);
    }

    f.solve();

    read(q);
    while (q--) {
      int fz, fm; read(fz, fm);

      if (fm > 1ll * fz * (int)costs.size()) {
        write("NaN\n");
        continue;
      }

      int need = fm / fz; if (fm % fz) need++;

      Frac ans = make(1ll * fz * costs[need - 1], 1ll * fm);
      Frac delta = make(1ll * need * fz - fm, 1ll * fm);
      ll val = costs[need - 1];
      if (need >= 2) val -= costs[need - 2];
      ans = sub(ans, mul(delta, val));

      write(ans.first, '/', ans.second, '\n');
    }
  }
  return 0;
}