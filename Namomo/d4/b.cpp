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

  ll a[maxn << 2], tag[maxn << 2];
  void pushup(int rt) {
    a[rt] = a[rt << 1] + a[rt << 1 | 1];
  }
  void pushdown(int rt, int ln, int rn) {
    if (tag[rt] == 0) return ;
    ll t = tag[rt];
    tag[rt << 1] += t;
    tag[rt << 1 | 1] += t;
    a[rt << 1] += 1ll * t * ln;
    a[rt << 1 | 1] += 1ll * t * rn;
    tag[rt] = 0;
  }
  void build(int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      a[rt] = ::a[l];
      return ;
    }
    int m = (l + r) / 2;
    build(lson);
    build(rson);
    pushup(rt);
  }

  void update(int L, int R, int x, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      a[rt] += 1ll * x * (r - l + 1);
      tag[rt] += x;
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt, m - l + 1, r - m);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
  }

  ll query(int L, int R, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) return a[rt];
    int m = (l + r) / 2;
    pushdown(rt, m - l + 1, r - m);
    ll ans = 0;
    if (L <= m) ans += query(L, R, lson);
    if (R > m) ans += query(L, R, rson);
    return ans;
  }
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  SegT::build();
  for (int i = 1; i <= q; i++) {
    int op;
    scanf("%d", &op);
    if (op == 2) {
      int l, r;
      scanf("%d%d", &l, &r);
      printf("%lld\n", SegT::query(l, r));
    } else if (op == 1) {
      int l, r, x;
      scanf("%d%d%d", &l, &r, &x);
      SegT::update(l, r, x);
    }
  }
  return 0;
}