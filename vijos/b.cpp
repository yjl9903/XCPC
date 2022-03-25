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
const int maxn = 400000 + 5;

namespace FastIO {
  const int SIZE = (1 << 21) + 1;
  char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[70]; int f, qr;
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

namespace UndirectedGraph {
  struct Edge {
    int to, nxt;
  } E[maxn];
  int ecnt = 1, head[maxn], vis[maxn];
  
  void adde(int u, int v) {
    E[++ecnt] = { v, head[u] };
    head[u] = ecnt;
  }

  int n, m, deg[maxn], ans[maxn], tot;

  void dfs(int u) {
    for (int& i = head[u]; i; i = E[i].nxt) {
      if (vis[i / 2]) continue;
      vis[i / 2] = true;
      int id = (i / 2) * (i % 2 == 0 ? 1 : -1);
      int v = E[i].to;
      dfs(v);
      ans[++tot] = id;
    }
  }
  
  void solve() {
    read(n, m);
    for (int i = 1; i <= m; i++) {
      int u, v;
      read(u, v);
      deg[u]++;
      deg[v]++;
      adde(u, v);
      adde(v, u);
    }
    for (int i = 1; i <= n; i++) {
      if (deg[i] % 2 == 1) {
        puts("NO");
        return ;
      }
    }
    for (int i = 1; i <= n; i++) {
      if (head[i]) {
        dfs(i);
        break;
      }
    }
    if (tot == m) {
      puts("YES");
      for (int i = m; i >= 1; i--) {
        write(ans[i], " \n"[i == 1]);
      }
    } else {
      puts("NO");
    }
  }
}

namespace DirectedGraph {
  struct Edge {
    int to, nxt;
  } E[maxn];
  int ecnt, head[maxn], vis[maxn];
  void adde(int u, int v) {
    E[++ecnt] = { v, head[u] };
    head[u] = ecnt;
  }
  
  int n, m, ind[maxn], oud[maxn], ans[maxn], tot;

  void dfs(int u) {
    for (int& i = head[u]; i; i = E[i].nxt) {
      if (vis[i]) continue;
      vis[i] = true;
      int id = i;
      int v = E[i].to;
      dfs(v);
      ans[++tot] = id;
    }
  }

  void solve() {
    read(n, m);
    for (int i = 1; i <= m; i++) {
      int u, v;
      read(u, v);
      oud[u]++;
      ind[v]++;
      adde(u, v);
    }
    for (int i = 1; i <= n; i++) {
      if (ind[i] != oud[i]) {
        puts("NO");
        return ;
      }
    }
    for (int i = 1; i <= n; i++) {
      if (head[i]) {
        dfs(i);
        break;
      }
    }
    if (tot == m) {
      puts("YES");
      for (int i = m; i >= 1; i--) {
        write(ans[i], " \n"[i == 1]);
      }
    } else {
      puts("NO");
    }
  }
}

int main() {
  int T;
  read(T);
  if (T == 1) {
    UndirectedGraph::solve();
  } else if (T == 2) {
    DirectedGraph::solve();
  }
  return 0;
}