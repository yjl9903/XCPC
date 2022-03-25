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
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;
const int maxm = 1000000 + 5;

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

int n, q, nn, ans[maxm];
vector<int> lsh;

int gid(int x) {
  return lower_bound(begin(lsh), end(lsh), x) - begin(lsh) + 1;
}

namespace BIT {
  int a[maxn];
  void clear() {
    for (int i = 0; i <= n + 1; i++) a[i] = 0;
  }
  void update(int i, int x) {
    for (; i <= n + 1; i += i & -i) a[i] += x;
  }
  int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
  }
  int query(int l, int r) {
    return query(r) - query(l - 1);
  }
}
namespace nBIT {
  int a[maxm];
  void clear() {
    for (int i = 0; i <= nn; i++) a[i] = inf;
  }
  void reset(int i) {
    i = nn + i + 1;
    for (; i <= nn; i += i & -i) a[i] = inf;
  }
  void update(int i, int x) {
    i = nn + i + 1;
    for (; i <= nn; i += i & -i) a[i] = min(a[i], x);
  }
  int query(int i) {
    i = nn + i + 1;
    int r = inf;
    for (; i; i -= i & -i) r = min(a[i], r);
    return r;
  }
}
namespace xBIT {
  int a[maxm];
  void clear() {
    for (int i = 1; i <= nn; i++) a[i] = -inf;
  }
  void reset(int i) {
    for (; i <= nn; i += i & -i) a[i] = -inf;
  }
  void update(int i, int x) {
    for (; i <= nn; i += i & -i) a[i] = max(a[i], x);
  }
  int query(int i) {
    int r = -inf;
    for (; i; i -= i & -i) r = max(a[i], r);
    return r;
  }
}

struct Ope {
  int x, y, z, h, tp;
} ope1[maxm], ope2[maxm], ope3[maxm];
int isQ[maxm], c1, c2, c3;

bool cmpy(const Ope& a, const Ope& b) {
  if (a.y == b.y) return a.x < b.x;
  return a.y < b.y;
}
bool cmpz(const Ope& a, const Ope& b) {
  if (a.z == b.z) return a.x < b.x;
  return a.z < b.z;
}

void cdq2(int l, int r) {
  if (l >= r) return ;
  int m = (l + r) / 2;
  cdq2(l, m);
  c3 = 0;
  for (int i = l; i <= m; i++) if (ope2[i].tp > 0) ope3[c3++] = ope2[i];
  for (int i = m + 1; i <= r; i++) if (ope2[i].tp < 0) ope3[c3++] = ope2[i];
  sort(ope3, ope3 + c3, cmpz);
  for (int i = 0; i < c3; i++) {
    auto q = ope3[i];
    if (q.tp == 1) {
      xBIT::update(q.h, q.h);
    } else if (q.tp == 2) {
      nBIT::update(q.h, -q.h);
    } else if (q.tp == -1) {
      int rk = xBIT::query(q.h);
      if (1 <= rk && rk <= nn) {
        ans[q.x] = min(ans[q.x], lsh[q.h - 1] - lsh[rk - 1]);
      }
    } else if (q.tp == -2) {
      int rk = nBIT::query(q.h);
      if (1 <= rk && rk <= nn) {
        ans[q.x] = min(ans[q.x], lsh[rk - 1] - lsh[-q.h - 1]);
      }
    }
  }
  for (int i = 0; i < c3; i++) {
    auto q = ope3[i];
    if (q.tp == 1) {
      xBIT::reset(q.h);
    } else if (q.tp == 2) {
      nBIT::reset(q.h);
    }
  }
  cdq2(m + 1, r);
}
void cdq(int l, int r) {
  if (l >= r) return ;
  int m = (l + r) / 2;
  cdq(l, m);
  c2 = 0;
  for (int i = l; i <= m; i++) if (ope1[i].tp > 0) ope2[c2++] = ope1[i];
  for (int i = m + 1; i <= r; i++) if (ope1[i].tp < 0) ope2[c2++] = ope1[i];
  sort(ope2, ope2 + c2, cmpy);
  cdq2(0, c2 - 1);
  cdq(m + 1, r);
}

int main() {
  int T = gi();
  while (T--) {
    n = gi(); q = gi();
    BIT::clear();
    lsh.clear();
    c1 = 0;
    for (int i = 1, x, y, h; i <= q; i++) {
      isQ[i] = gi();
      if (isQ[i] == 0) {
        x = gi(); h = gi();
        BIT::update(x, 1);
        ope1[c1++] = (Ope){ i, -x, x, h, 1 };
        ope1[c1++] = (Ope){ i, -x, x, -h, 2 };
      } else if (isQ[i] == 1) {
        x = gi(); y = gi(); h = gi();
        if (BIT::query(x, y) == 0) {
          ans[i] = -1;
        } else {
          ans[i] = 2e9;
          ope1[c1++] = (Ope){ i, -x, y, h, -1 };
          ope1[c1++] = (Ope){ i, -x, y, -h, -2 };
        }
      }
      lsh.push_back(h);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
    nn = (int)lsh.size();
    nBIT::clear(); xBIT::clear();
    for (int i = 0; i < c1; i++) {
      if (ope1[i].h > 0) {
        ope1[i].h = gid(ope1[i].h);
      } else {
        ope1[i].h = -gid(-ope1[i].h);
      }
    }
    cdq(0, c1 - 1);
    for (int i = 1; i <= q; i++) {
      if (isQ[i]) {
        printf("%d\n", ans[i]);
      }
    }
  }
  return 0;
}