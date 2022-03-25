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
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;
const int B = 31;

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

int n, q, g[18][maxn], R[maxn * 30];
vector<PII> bag[maxn];

int qand(int l, int r) {
  int k = __lg(r - l + 1);
  return g[k][l] & g[k][r - (1 << k) + 1];
}

int tot, root[maxn], ls[maxn * 30 * 30], rs[maxn * 30 * 30], sum[maxn * 30 * 30];
void update(int i, int x, int pre, int l, int r, int& rt) {
  rt = ++tot;
  ls[rt] = ls[pre];
  rs[rt] = rs[pre];
  sum[rt] = sum[pre] + x;
  if (l == r) return ;
  int m = (l + r) / 2;
  if (i <= m) update(i, x, ls[pre], lson);
  else update(i, x, rs[pre], rson);
}
int query(int L, int R, int l, int r, int rt) {
  if (!rt) return 0;
  if (L <= l && r <= R) return sum[rt];
  int m = (l + r) / 2, ans = 0;
  if (L <= m) ans += query(L, R, lson);
  if (R > m) ans += query(L, R, rson);
  return ans;
}

int main() {
  read(n);
  for (int i = 1; i <= n; i++) {
    read(g[0][i]);
  }
  for (int j = 1; j < 18; j++) {
    for (int i = 1; i + (1 << j) <= n + 1; i++) {
      g[j][i] = (g[j - 1][i] & g[j - 1][i + (1 << (j - 1))]);
    }
  }
  vector<int> lsh;
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      int l = j, r = n, ans = j, g = qand(i, j);
      while (l <= r) {
        int m = (l + r) / 2;
        if (qand(i, m) == g) {
          ans = m; l = m + 1;
        } else {
          r = m - 1;
        }
      }
      lsh.push_back(g);
      bag[i].emplace_back(j, g);
      j = ans;
    }
  }

  sort(begin(lsh), end(lsh));
  lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
  auto gid = [&lsh](int x) {
    return lower_bound(begin(lsh), end(lsh), x) - begin(lsh) + 1;
  };

  for (int i = n; i >= 1; i--) {
    root[i] = root[i + 1];
    for (auto& x: bag[i]) {
      int id = gid(x.second);
      if (R[id] == 0 || x.first < R[id]) {
        if (R[id]) {
          update(R[id], -1, root[i], 1, n, root[i]);
        }
        update(x.first, 1, root[i], 1, n, root[i]);
        R[id] = x.first;
      }
    }
  }

  read(q);
  int ans = 0;
  while (q--) {
    int ql, qr;
    read(ql, qr);
    ql = (ql ^ ans) % n + 1;
    qr = (qr ^ ans) % n + 1;
    if (ql > qr) swap(ql, qr);
    write(ans = query(ql, qr, 1, n, root[ql]), '\n');
  }
  return 0;
}