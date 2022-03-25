#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, q, a[maxn];

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  ll sum[maxn * 4];
  int mn[maxn * 4], tag[maxn * 4];
  void pushup(int rt) {
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
  }
  void pushdown(int rt, int ln, int rn) {
    if (tag[rt] == 0) return ;
    int t = tag[rt];
    sum[rt << 1] = 1ll * t * ln;
    sum[rt << 1 | 1] = 1ll * t * rn;
    mn[rt << 1] = t;
    mn[rt << 1 | 1] = t;
    tag[rt << 1] = t;
    tag[rt << 1 | 1] = t;
    tag[rt] = 0;
  }
  void build(int l = 1, int r = n, int rt = 1) {
    tag[rt] = 0;
    if (l == r) {
      sum[rt] = mn[rt] = a[l];
      return ;
    }
    int m = (l + r) / 2;
    build(lson);
    build(rson);
    pushup(rt);
  }

  int qpos(int k, int l = 1, int r = n, int rt = 1) {
    if (mn[rt] > k) return inf;
    if (l == r) return l;
    int m = (l + r) / 2;
    pushdown(rt, m - l + 1, r - m);
    if (mn[rt << 1] <= k) return qpos(k, lson);
    else return qpos(k, rson);
  }
  void update(int L, int R, int x, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      sum[rt] = 1ll * x * (r - l + 1);
      mn[rt] = tag[rt] = x;
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt, m - l + 1, r - m);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
  }

  int query(int L, int& w, int l = 1, int r = n, int rt = 1) {
    if (w < mn[rt]) return 0;
    if (L <= l && w >= sum[rt]) {
      w -= sum[rt];
      return r - l + 1;
    }
    int m = (l + r) / 2;
    int ans = 0;
    pushdown(rt, m - l + 1, r - m);
    if (L <= m) ans += query(L, w, lson);
    ans += query(L, w, rson);
    return ans;
  }
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  SegT::build();
  while (q--) {
    int op, x, y;
    scanf("%d%d%d", &op, &x, &y);
    if (op == 1) {
      int pos = SegT::qpos(y);
      if (pos <= x) {
        SegT::update(pos, x, y);
      }
    } else if (op == 2) {
      printf("%d\n", SegT::query(x, y));
    }
  }
  return 0;
}