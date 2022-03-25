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

int n, q, c[maxn], ans[maxn];

void update(int i, int x) {
  for (; i <= n; i += i & -i) c[i] += x;
}
int query(int i) {
  int r = 0;
  for (; i; i -= i & -i) r += c[i];
  return r;
}

struct Rect {
  int xa, ya, xb, yb;
} R[maxn];

struct Update {
  int l, r, w, id;

  bool operator < (const Update& rhs) const {
    if (l == rhs.l) {
      return id < rhs.id;
    }
    return l > rhs.l;
  }
};
vector<Update> upd;

struct Heap {
  priority_queue<int> ins, del;

  void push(int x) {
    ins.push(x);
  }
  void pop(int x) {
    del.push(x);
  }
  bool empty() {
    return ins.size() == del.size();
  }
  int top() {
    while (!del.empty() && del.top() == ins.top()) {
      del.pop();
      ins.pop();
    }
    return ins.top();
  }
};

int width, sum, cnt;

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  // set<int> a[maxn];
  Heap fmx[maxn], fmn[maxn];
  void insert(int L, int R, int tp, int x, int l = 0, int r = 2000, int rt = 1) {
    if (L <= l && r <= R) {
      if (tp) {
        fmx[rt].push(x);
        fmn[rt].push(-x);
      } else {
        fmx[rt].pop(x);
        fmn[rt].pop(-x);
      }
      return ;
    }
    int m = (l + r) / 2;
    if (L <= m) insert(L, R, tp, x, lson);
    if (R > m) insert(L, R, tp, x, rson);
  }

  void dfs(int mx, int mn, int l = 0, int r = 2000, int rt = 1) {
    if (!fmx[rt].empty()) {
      mx = max(mx, fmx[rt].top());
      mn = min(mn, -fmn[rt].top());
    }
    if (l == r) {
      if (mn != inf && mx != -inf) {
        sum += width;
        upd.push_back({ mn, mx, width, 0 });
      }
      return ;
    }
    int m = (l + r) / 2;
    dfs(mx, mn, lson);
    dfs(mx, mn, rson);
  }
}

int main() {
  read(n, q);
  upd.reserve(2001 * 2001);
  vector<PII> evs;
  evs.reserve(n + n);
  for (int i = 1; i <= n; i++) {
    read(R[i].ya, R[i].xa, R[i].yb, R[i].xb);
    evs.emplace_back(R[i].xa, +i);
    evs.emplace_back(R[i].xb, -i);
  }
  sort(evs.begin(), evs.end());
  for (int i = 0, j = 0; i < n + n; i = j) {
    while (j < n + n && evs[j].first == evs[i].first) {
      int id = evs[j].second;
      if (id > 0) {
        SegT::insert(R[id].ya, R[id].yb - 1, 1, id);
        cnt++;
      } else {
        id = -id;
        SegT::insert(R[id].ya, R[id].yb - 1, 0, id);
        cnt--;
      }
      j++;
    }
    if (cnt > 0) {
      assert(j < n + n);
      width = evs[j].first - evs[i].first;
      SegT::dfs(-inf, inf);
    }
  }
  for (int i = 1; i <= q; i++) {
    int s, t;
    read(s, t);
    upd.push_back({ s, t, 0, i });
  }
  sort(upd.begin(), upd.end());
  for (int i = n, j = 0; i >= 1 && j < upd.size(); i--) {
    while (j < upd.size() && upd[j].l == i) {
      int id = upd[j].id;
      if (id == 0) {
        update(upd[j].r, upd[j].w);
      } else {
        ans[id] = query(upd[j].r);
      }
      j++;
    }
  }
  dbg(sum);
  for (int i = 1; i <= q; i++) {
    printf("%d\n", sum - ans[i]);
  }
  return 0;
}