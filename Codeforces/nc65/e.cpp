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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

struct fastIO {
  char s[100000]; int it,len;
  fastIO() { it = len = 0; }
  inline char get() {
    if (it < len) return s[it++];
    it = 0; len = fread(s, 1, 100000, stdin);
    if (len == 0) return EOF;
    else return s[it++];
  }
  bool notend() {
    char c = get();
    while(c == ' ' || c == '\n') c = get();
    if (it > 0) it--;
    return c != EOF;
  }
} buff;
inline int gi() {
  int r = 0; bool ng = 0;
  char c = buff.get();
  while (c != '-' && (c < '0' || c > '9')) c = buff.get();
  if (c == '-') ng = 1, c = buff.get();
  while (c >= '0' && c <= '9') r = r * 10 + c - '0', c = buff.get();
  return ng ? -r : r;
}

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
inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}
inline int inv(int x) {
  return qpow(x, mod - 2);
}

struct E { int to, nxt; } e[maxn];
int ecnt, head[maxn];
void addE(int u, int v) {
  e[++ecnt] = { v, head[u] };
  head[u] = ecnt;
}

int n, m;

int cnt, bel[maxn];
namespace Tarjan {
  E e[maxn];
  int ecnt, head[maxn];
  void adde(int u, int v) {
    e[++ecnt] = { v, head[u] };
    head[u] = ecnt;
  }

  int tot, dfn[maxn], low[maxn], st[maxn], top, vis[maxn];
  void dfs(int u, int f) {
    dfn[u] = low[u] = ++tot;
    st[++top] = u; vis[u] = 1;
    int k = 0;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].to;
      if (v == f && !k) {
        k++; continue;
      }
      if (!dfn[v]) {
        dfs(v, u); low[u] = min(low[u], low[v]);
      } else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
      cnt++; int t = 0;
      do {
        t = st[top--];
        bel[t] = cnt;
        vis[t] = 0;
      } while (t != u);
    }
  }
  void scc(int n) {
    for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(i, 0);
    for (int i = 1; i <= n; i++) {
      int u = bel[i];
      for (int i = head[u]; i; i = e[i].nxt) {
        int v = bel[e[i].to];
        if (u != v) {
          addE(u, v);
        }
      }
    }
  }
}

int dep[maxn], mxd;
void dfs(int u, int f) {
  if (dep[u] >= dep[mxd]) mxd = u;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].to;
    if (v == f) continue;
    dep[v] = dep[u] + 1;
    dfs(v, u);
  }
}

int main() {
  n = gi(); m = gi();
  for (int i = 1; i <= m; i++) {
    int u = gi();
    int v = gi();
    Tarjan::adde(u, v);
    Tarjan::adde(v, u);
  }
  Tarjan::scc(n);
  dfs(1, 0);
  int rt = mxd; mxd = 0;
  for (int i = 0; i <= cnt; i++) dep[i] = 0;
  dfs(rt, 0);
  cout << mul(inv(m + 1), (cnt - 1) - dep[mxd]);
  return 0;
}