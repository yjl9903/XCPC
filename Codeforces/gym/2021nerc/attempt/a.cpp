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
const int maxn = 500000 + 5;

int n, a[maxn];

struct SegTree {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  int a[maxn << 2], tag[maxn << 2];
  void build(int l = 0, int r = n, int rt = 1) {
    tag[rt] = a[rt] = 0;
    if (l == r) {
      return ;
    }
    int m = (l + r) / 2;
    build(lson);
    build(rson);
  }
  void upd(int rt, int x) {
    a[rt] += x;
    tag[rt] += x;
  }
  void pushdown(int rt) {
    if (tag[rt] == 0) return ;
    upd(rt << 1, tag[rt]);
    upd(rt << 1 | 1, tag[rt]);
    tag[rt] = 0;
  }
  void update(int L, int R, int x, int l = 0, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      upd(rt, x);
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    a[rt] = max(a[rt << 1], a[rt << 1 | 1]);
  }
  int query(int L, int R, int l = 0, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      return a[rt];
    }
    int m = (l + r) / 2;
    int ans = 0;
    pushdown(rt);
    if (L <= m) ans = query(L, R, lson);
    if (R > m) ans = max(ans, query(L, R, rson));
    return ans;
  }
} f, g;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    f.build();
    g.build();
    for (int i = 1; i <= n; i++) {
      {
        int val = max(f.query(0, a[i]), g.query(0, a[i]));
        int src = f.query(a[i], a[i]);
        if (val + 1 > src) {
          f.update(a[i], a[i], val + 1 - src);
        }
      }
      {
        g.update(a[i], n, 1);
      }
    }
    printf("%d\n", max(f.query(0, n), g.query(0, n)));
  }
  return 0;
}