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

int n, q, b[maxn];
vector<int> ans;

struct fhqTreap {
  int root, tot;
  int ch[maxn][2], size[maxn], key[maxn], rnd[maxn], rev[maxn];
  int val[maxn], mn[maxn];
  ll sum[maxn];
  void clear() {
    root = tot = 0;
    mn[0] = 1e9 + 7;
    sum[0] = 0;
    val[0] = 0;
  }
  fhqTreap() {
    clear();
  }
  int node(int v, int x) {
    tot++;
    key[tot] = v;
    val[tot] = x;
    mn[tot] = x;
    sum[tot] = x;
    rnd[tot] = rand();
    size[tot] = 1;
    ch[tot][0] = ch[tot][1] = rev[tot] = 0;
    return tot;
  }
  void pushup(int x) {
    size[x] = size[ch[x][0]] + size[ch[x][1]] + 1;
    sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + val[x];
    mn[x] = val[x];
    mn[x] = min(mn[x], mn[ch[x][0]]);
    mn[x] = min(mn[x], mn[ch[x][1]]);
  }
  void pushdown(int x) {
    if (rev[x] == 0) return;
    swap(ch[x][0], ch[x][1]);
    if (ch[x][0]) rev[ch[x][0]] ^= 1;
    if (ch[x][1]) rev[ch[x][1]] ^= 1;
    rev[x] = 0;
  }
  void split(int now, int k, int &x, int &y) {
    if (!now) {
      x = y = 0; return;
    }
    pushdown(now);
    if (size[ch[now][0]] < k) {
      x = now;
      split(ch[now][1], k - size[ch[now][0]] - 1, ch[now][1], y);
    } else {
      y = now;
      split(ch[now][0], k, x, ch[now][0]);
    }
    pushup(now);
  }
  void splitByMin(int u, int k, int &x, int &y) {
    if (!u) {
      x = y = 0; return;
    }
    pushdown(u);
    if (mn[ch[u][1]] < k || val[u] < k) {
      x = u;
      splitByMin(ch[u][1], k, ch[u][1], y);
    } else {
      y = u;
      splitByMin(ch[u][0], k, x, ch[u][0]);
    }
    pushup(u);
  }
  int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (rnd[x] < rnd[y]) {
      pushdown(x);
      ch[x][1] = merge(ch[x][1], y);
      pushup(x);
      return x;
    } else {
      pushdown(y);
      ch[y][0] = merge(x, ch[y][0]);
      pushup(y);
      return y;
    }
  }
  // int findx(int now, int k) {
  //   int u = now;
  //   while (k != size[ch[u][0]] + 1) {
  //     if (k <= size[ch[u][0]]) u = ch[u][0];
  //     else k -= size[ch[u][0]] + 1, u = ch[u][1];
  //   }
  //   return u;
  // }
  void reverse(int l, int r) {
    int x, y, z;
    split(root, l - 1, x, y);
    split(y, r - l + 1, y, z);
    rev[y] ^= 1;
    root = merge(x, merge(y, z));
  }
  int query(int x) {
    int u = findx(root, x);
    return val[u];
  }
  ll push(int x, int y) {
    if (x == 1) return 0;
    if (y > query(x)) return 0;
    int a, b;
    split(root, x, a, b);
    if (mn[a] >= y) {
      root = merge(a, b);
      return 0;
    }

    int c, d;
    splitByMin(a, y, c, d);
    assert(c && d);
    ll ans = sum[d] - 1ll * size[d] * (y - 1);

    int p, q, m, z;
    split(c, size[c] - 1, m, z);
    split(d, 1, p, q);

    val[z] += val[p] - y + 1;
    val[p] = y - 1;
    sum[z] = mn[z] = val[z];
    sum[p] = mn[p] = val[p];
    // pushup(z);
    // pushup(p);

    root = merge(merge(merge(m, z), merge(q, p)), b);
    assert(size[root] == n);
    return ans;
  }
  void print(int x) {
    if (!x) return;
    pushdown(x);
    print(ch[x][0]);
    ans.push_back(val[x]);
    print(ch[x][1]);
  }
} f;

int main() {
  int T;
  read(T);
  while (T--) {
    read(n, q);
    f.clear();
    for (int i = 1; i <= n; i++) {
      read(b[i]);
      f.root = f.merge(f.root, f.node(i, b[i]));
    }
    int op, x, y;
    for (int i = 1; i <= q; i++) {
      read(op, x);
      if (op == 1) {
        read(y);
        // dbg(x, y);
        write(f.push(x, y), '\n');
        // printf("%lld\n", f.push(x, y));
      } else if (op == 2) {
        write(f.query(x), '\n');
        // printf("%d\n", f.query(x));
      }
    }
    ans.clear();
    f.print(f.root);
    assert(ans.size() == n);
    for (int i = 0; i < n; i++) {
      if (i) write(' ');
      write(ans[i]);
    }
    write('\n');
  }
  return 0;
}