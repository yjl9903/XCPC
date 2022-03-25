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
const int maxn = 50000 + 5;

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


int n, q;
vector<int> edge[maxn];

namespace LCA {
  int st[maxn], ed[maxn], dep[maxn];
  int euler[maxn * 2], cnt;
  int dp[17][maxn * 2];
  void dfs(int u, int f) {
    euler[++cnt] = u;
    st[u] = cnt;
    for (int v: edge[u]) {
      if (v == f) continue;
      dep[v] = dep[u] + 1;
      dfs(v, u);
      euler[++cnt] = u;
    }
    ed[u] = cnt;
  }
  void build() {
    dep[1] = 0;
    cnt = 0;
    dfs(1, 0);
    for (int i = 1; i <= cnt; i++) {
      dp[0][i] = euler[i];
    }
    for (int j = 1; j < 17; j++) {
      for (int i = 1; i + (1 << j) <= cnt + 1; i++) {
        int l = dp[j - 1][i];
        int r = dp[j - 1][i + (1 << (j - 1))];
        if (dep[l] < dep[r]) {
          dp[j][i] = l;
        } else {
          dp[j][i] = r;
        }
      }
    }
  }
  int qlca(int u, int v) {
    int l = st[u], r = st[v];
    if (l > r) swap(l, r);
    int k = __lg(r - l + 1);
    int x = dp[k][l], y = dp[k][r - (1 << k) + 1];
    if (dep[x] < dep[y]) {
      return x;
    } else {
      return y;
    }
  }
  int qdis(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[qlca(u, v)];
  }
}

int vis[maxn], siz[maxn], fa[maxn], sum, mn, rt;
void getrt(int u, int f) {
  siz[u] = 1;
  int t = 0;
  for (int v: edge[u]) {
    if (v == f || vis[v]) continue;
    getrt(v, u); siz[u] += siz[v];
    t = max(t, siz[v]);
  }
  t = max(t, sum - siz[u]);
  if (t < mn) mn = t, rt = u;
}
int getrt(int u) {
  sum = siz[u];
  mn = 1e9;
  rt = 0;
  getrt(u, 0);
  return rt;
}

int id[maxn];
ll allV, blkSum[maxn], val[maxn];
int blkCnt[maxn];
vector<int> blkC[maxn];
vector<ll> blkS[maxn];
void solve(int u) {
  vis[u] = true;
  int tot = 0;
  for (int v: edge[u]) {
    if (vis[v]) continue;
    int vRt = getrt(v);
    fa[vRt] = u;
    id[vRt] = tot++;
    blkC[u].push_back(0);
    blkS[u].push_back(0ll);
    solve(vRt);
  }
}

void update(int u, int w) {
  int su = u;
  allV += w;
  blkCnt[u]++;
  while (fa[u]) {
    int rt = fa[u];
    blkCnt[rt]++;
    blkC[rt][id[u]]++;
    blkSum[rt] += hld::qdis(su, rt);
    blkS[rt][id[u]] += hld::qdis(su, rt);
    u = rt;
  }
}
ll query(int u) {
  int su = u;
  ll ans = allV - blkSum[u];
  while (fa[u]) {
    int rt = fa[u];
    ll cur = (blkSum[rt] - blkS[rt][id[u]]) + 1ll * (blkCnt[rt] - blkC[rt][id[u]]) * hld::qdis(su, rt);
    ans -= cur;
    u = rt;
  }
  return ans;
}

int main() {
  int T; read(T);
  while (T--) {
    read(n, q);
    allV = 0;
    for (int i = 1; i <= n; i++) {
      edge[i].clear();

      blkC[i].clear();
      blkS[i].clear();
      blkCnt[i] = 0;
      blkSum[i] = 0;

      vis[i] = false;
      val[i] = id[i] = fa[i] = 0;
    }
    for (int i = 2, u, v; i <= n; i++) {
      read(u, v);
      edge[u].push_back(v);
      edge[v].push_back(u);
    }

    hld::build();

    siz[1] = n;
    int rt = getrt(1);
    solve(rt);

    while (q--) {
      int op, u, w;
      read(op, u);
      if (op == 1) {
        read(w);
        update(u, w);
      } else if (op == 2) {
        ll ans = query(u) + val[u];
        if (ans > 0) {
          val[u] = -query(u);
        }
      } else if (op == 3) {
        ll ans = query(u) + val[u];
        write(ans, '\n');
      }
    }
  }
  return 0;
}