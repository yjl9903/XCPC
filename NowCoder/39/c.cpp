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
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
using ll = long long;
using PII = pair<int,int>;
int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, q, b[maxn];

ll a[maxn << 2], first[maxn << 2], det[maxn << 2];

void build(int l = 1, int r = n, int rt = 1) {
  if (l == r) {
    a[rt] = b[l] % 111546435;
    return ;
  }
  int m = (l + r) / 2;
  build(lson); build(rson);
  a[rt] = (a[rt << 1] + a[rt << 1 | 1]) % 111546435;
}
void pushdown(int rt, int ln, int rn) {
  (first[rt << 1] += first[rt]) %= 111546435;
  (det[rt << 1] += det[rt]) %= 111546435;
  (a[rt << 1] += first[rt] * ln + det[rt] * (ln * (ln - 1) / 2)) %= 111546435;

  (first[rt << 1 | 1] += first[rt] + ln * det[rt]) %= 111546435;
  (det[rt << 1 | 1] += det[rt]) %= 111546435;
  (a[rt << 1 | 1] += (first[rt] + ln * det[rt]) * rn + det[rt] * (rn * (rn - 1) / 2)) %= 111546435;

  first[rt] = 0;
  det[rt] = 0;
}
void update(int L, int R, ll v, ll d, int l = 1, int r = n, int rt = 1) {
  if (L <= l && r <= R) {
    (first[rt] += v + (l - L) * d) %= 111546435;
    (det[rt] += d) %= 111546435;
    (a[rt] += (v + (l - L) * d) * (r - l + 1) + d * ((r - l) * (r - l + 1) / 2)) %= 111546435;
    return ;
  }
  int m = (l + r) / 2; pushdown(rt, m - l + 1, r - m);
  if (L <= m) update(L, R, v, d, lson);
  if (R > m) update(L, R, v, d, rson);
  a[rt] = (a[rt << 1] + a[rt << 1 | 1]) % 111546435;
}
int query(int L, int R, int l = 1, int r = n, int rt = 1) {
  // dbg(l, r, a[rt], first[rt], det[rt]);
  if (L <= l && r <= R) {
    return a[rt] % mod;
  }
  int m = (l + r) / 2; pushdown(rt, m - l + 1, r - m);
  ll ans = 0;
  if (L <= m) ans += query(L, R, lson);
  if (R > m) ans += query(L, R, rson);
  return ans % mod;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", b + i);
  }
  build();
  scanf("%d", &q);
  for (int i = 1, op, l, r; i <= q; i++) {
    scanf("%d%d%d", &op, &l, &r);
    if (op == 1) {
      int val, d; scanf("%d%d", &val, &d);
      update(l, r, val, d);
    } else if (op == 2) {
      scanf("%d", &mod);
      printf("%d\n", query(l, r) % mod);
    }
  }
  return 0;
}