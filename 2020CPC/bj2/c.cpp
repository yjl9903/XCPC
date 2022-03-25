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
const int maxn = 200000 + 5;

int n, m, a[maxn], b[maxn];
ll preb[maxn];

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  ll mx[maxn << 2], sum[maxn << 2];
  ll tag1[maxn << 2], tag2[maxn << 2];
  void pushup(int rt) {
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
  }
  void pushdown(int rt, int ln, int rn) {
    if (tag1[rt]) {
      ll t = tag1[rt];
      mx[rt << 1] += t;
      mx[rt << 1 | 1] += t;
      tag1[rt << 1] += t;
      tag1[rt << 1 | 1] += t;
      tag1[rt] = 0;
    }
    if (tag2[rt]) {
      ll t = tag2[rt];
      sum[rt << 1] += t * ln;
      sum[rt << 1 | 1] += t * rn;
      tag2[rt << 1] += t;
      tag2[rt << 1 | 1] += t;
      tag2[rt] = 0;
    }
  }
  void build(int l = 1, int r = n, int rt = 1) {
    tag1[rt] = tag2[rt] = 0;
    if (l == r) {
      mx[rt] = a[l] - preb[l];
      sum[rt] = b[l];
      return ;
    }
    int m = (l + r) / 2;
    build(lson);
    build(rson);
    pushup(rt);
  }

  void updateA(int i, int x, int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      mx[rt] += x - a[l];
      a[l] = x;
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt, m - l + 1, r - m);
    if (i <= m) updateA(i, x, lson);
    else updateA(i, x, rson);
    pushup(rt);
  }

  void updateBS(int i, int x, int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      sum[rt] += x;
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt, m - l + 1, r - m);
    if (i <= m) updateBS(i, x, lson);
    else updateBS(i, x, rson);
    pushup(rt);
  }

  void updateBX(int L, int R, int x, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      mx[rt] -= x;
      tag1[rt] -= x;
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt, m - l + 1, r - m);
    if (L <= m) updateBX(L, R, x, lson);
    if (R > m) updateBX(L, R, x, rson);
    pushup(rt);
  }

  ll qmax(int L, int R, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      return mx[rt];
    }
    int m = (l + r) / 2;
    pushdown(rt, m - l + 1, r - m);
    if (R <= m) {
      return qmax(L, R, lson);
    } else if (L > m) {
      return qmax(L, R, rson);
    } else {
      return max(qmax(L, R, lson), qmax(L, R, rson));
    }
  }

  ll qsum(int L, int R, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      return sum[rt];
    }
    int m = (l + r) / 2;
    pushdown(rt, m - l + 1, r - m);
    if (R <= m) {
      return qsum(L, R, lson);
    } else if (L > m) {
      return qsum(L, R, rson);
    } else {
      return qsum(L, R, lson) + qsum(L, R, rson);
    }
  }
}

int main() {
  while (scanf("%d%d", &n, &m) == 2) {
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", b + i);
      preb[i] = b[i] + preb[i - 1];
    }
    SegT::build();
    while (m--) {
      int op, x, y;
      scanf("%d%d", &op, &x);
      if (op == 1) {
        scanf("%d", &y);
        SegT::updateA(x, y);
      } else if (op == 2) {
        scanf("%d", &y);
        dbg(y - b[x]);
        SegT::updateBS(x, y - b[x]);
        SegT::updateBX(x, n, y - b[x]);
        b[x] = y;
        // for (int i = 1; i <= n; i++) {
        //   dbg(i, SegT::qsum(i, i));
        // }
      } else if (op == 3) {
        ll ans = SegT::qmax(1, x) + SegT::qsum(1, x);
        ans = max(ans, SegT::qsum(1, x));
        printf("%lld\n", ans);
      }
    }
  }
  return 0;
}