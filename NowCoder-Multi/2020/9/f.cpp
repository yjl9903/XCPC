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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

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

int n, m, pt[maxn];
vector<int> backet[maxn], pos[maxn + maxn];

struct BIT {
  static const int R = 1 << 22;
  int a[R + 5];
  inline int lowbit(int x) { return x & -x; }
  void insert(int i, int x = 1) {
    for (; i < R; i += lowbit(i)) a[i] += x;
  }
  int findx(int p, int rk) {
    // if (p > R) return -1;
    if (p & 1) {
      // if (p + (a[p] < rk) > R) return -1;
      return p + (a[p] < rk);
    } else {
      if (rk > a[p]) return findx(p + lowbit(p) / 2, rk - a[p]);
      else return findx(p - lowbit(p) / 2, rk);
    }
  }
  int findx(int rk) {
    return findx(R >> 1, rk);
  }
} f;

int main() {
  read(n, m);
  vector<int> lsh;
  lsh.reserve(maxn);
  for (int i = 1; i <= n; i++) {
    int k, x;
    read(k);
    backet[i].reserve(k);
    while (k--) {
      read(x);
      backet[i].push_back(x);
      lsh.push_back(x);
    }
  }
  sort(begin(lsh), end(lsh));
  lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
  assert(lsh.size() < maxn + maxn);
  auto gid = [&lsh](int x) {
    return lower_bound(begin(lsh), end(lsh), x) - begin(lsh) + 1;
  };
  int sz = 0;
  for (int i = 1; i <= n; i++) {
    sort(begin(backet[i]), end(backet[i]));
    pt[i] = 0;
    if (!backet[i].empty()) {
      backet[i].resize(unique(begin(backet[i]), end(backet[i])) - begin(backet[i]));
      sz++;
      f.insert(gid(backet[i].front()));
      for (int& x: backet[i]) {
        x = gid(x);
        // pos[x].push_back(i);
      }
    }
  }
  int ans = (int)1e9 + 7;
  for (int i = 1; i <= (int)lsh.size() && sz >= m; i++) {
    ans = min(ans, lsh[f.findx(m) - 1] - lsh[i - 1]);
    for (int& x: pos[i]) {
      f.insert(backet[x][pt[x]], -1);
      pt[x]++;
      if (pt[x] < backet[x].size()) {
        f.insert(backet[x][pt[x]]);
      } else {
        sz--;
      }
    }
  }
  write(ans, '\n');
  return 0;
}