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
const int inf = 1 << 30;
const int maxn = 100000 + 5;

struct fastIO {
  static const int SIZE = 1 << 20;
  char s[SIZE]; int it, len;
  fastIO() { it = len = 0; }
  inline char get() {
    if (it < len) return s[it++];
    it = 0; len = fread(s, 1, SIZE, stdin);
    if (len == 0) return EOF;
    else return s[it++];
  }
  inline bool notend() {
    char c = get();
    while (c == ' ' || c == '\n') c = get();
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

namespace Output {
  const int SIZE = 1 << 20;
  char oBuf[SIZE], buf[64], *oS = oBuf, *oT = oS + SIZE - 1;
  inline void flush() {
    fwrite(oBuf, 1, oS - oBuf, stdout);
    oS = oBuf;
  }
  inline void put(char ch) {
    *oS++ = ch;
    if (oS == oT) flush();
  }
  inline void write(char ch) {
    put(ch);
  }
  inline void write(const char* it) {
    while (*it) put(*it), ++it;
  }
  template<typename T>
  inline void write(T x) {
    if (!x) put('0');
    if (x < 0) put('-'), x = -x;
    int qr = 0;
    while (x) buf[++qr] = x % 10 + '0', x /= 10;
    while (qr) put(buf[qr--]);
  }
  template<typename T, typename... Tails>
  inline void write(T x, Tails... y) {
    write(x); write(y...);
  }
  struct Flusher_ { ~Flusher_() { flush(); } } io_flusher_;
}

int n, q, ans[maxn], cnt[maxn], mx;
int ecnt, head[maxn], pos[maxn], nxt[maxn];

void add(int u, int p) {
  ecnt++;
  pos[ecnt] = p;
  nxt[ecnt] = head[u];
  head[u] = ecnt;
}

struct Bit {
  int a[maxn];
  void update(int i, int x) {
    for (i++; i <= mx + 1; i += i & -i) a[i] += x;
  }
  int query(int i) {
    int r = 0;
    for (i++; i; i -= i & -i) r += a[i];
    return r;
  }
} f;

struct Node {
  int x, y, z, id;

  bool operator < (const Node& b) const {
    if (y != b.y) return y > b.y;
    return abs(id) < abs(b.id);
  }
} all[maxn * 6], b[maxn * 6];

void cdq(int l, int r) {
  if (l >= r) return ;
  int m = (l + r) / 2;
  cdq(l, m);
  cdq(m + 1, r);
  for (int i = l; i <= r; i++) b[i] = all[i];
  sort(b + l, b + m + 1);
  sort(b + m + 1, b + r + 1);
  int j = l;
  for (int i = m + 1; i <= r; i++) {
    for (; j <= m && b[j].y >= b[i].y; j++) {
      if (b[j].id == 0) {
        f.update(b[j].z, 1);
      }
    }
    if (b[i].id) {
      int val = f.query(b[i].z);
      if (b[i].id > 0) ans[b[i].id] -= val;
      else ans[-b[i].id] += val;
    }
  }
  for (j--; j >= l; j--) {
    if (b[j].id == 0) {
      f.update(b[j].z, -1);
    }
  }
}

int main() {
  int T = gi();
  while (T--) {
    n = gi();
    q = gi();
    mx = ecnt = 0;
    ms(head, 0);
    for (int i = 1; i <= n; i++) {
      int x = gi();
      mx = max(mx, x);
      add(x, i);
    }
    int cnt = 0;
    auto push = [&](int x, int y, int z, int id) {
      all[++cnt] = { x, y, z, id };
    };
    for (int i = 1; i <= q; i++) {
      int x0 = gi();
      int y0 = gi();
      int x1 = gi();
      int y1 = gi();
      mx = max(mx, y1);
      if (y0 > 0) {
        push(x0, x1, y0 - 1, -i);
      }
      push(x0, x1, y1, i);
      ans[i] = y1 - y0 + 1;
    }
    for (int i = 0; i <= mx; i++) {
      int last = n;
      for (int j = head[i]; j; j = nxt[j]) {
        int x = pos[j];
        if (x < last) {
          push(x + 1, last, i, 0);
        }
        last = x - 1;
      }
      if (last >= 1) {
        push(1, last, i, 0);
      }
    }
    sort(all + 1, all + cnt + 1, [](const Node& a, const Node& b) {
      if (a.x != b.x) return a.x < b.x;
      if (a.y != b.y) return a.y > b.y;
      return abs(a.id) < abs(b.id);
    });
    cdq(1, cnt);
    for (int i = 1; i <= q; i++) {
      Output::write(ans[i], '\n');
    }
  }
  return 0;
}