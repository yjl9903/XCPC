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

int n, q, ql[maxn], qr[maxn];
char s[maxn], f[maxn];

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  int a[maxn << 2][2], cov[maxn << 2];

  void pushup(int rt) {
    a[rt][0] = a[rt << 1][0] + a[rt << 1 | 1][0];
    a[rt][1] = a[rt << 1][1] + a[rt << 1 | 1][1];
  }
  void pushdown(int rt, int ln, int rn) {
    if (cov[rt] == -1) return ;
    int t = cov[rt];
    a[rt << 1][0] = a[rt << 1][1] = 0;
    a[rt << 1 | 1][0] = a[rt << 1 | 1][1] = 0;
    a[rt << 1][t] = ln;
    a[rt << 1 | 1][t] = rn;
    cov[rt << 1] = cov[rt << 1 | 1] = t;
    cov[rt] = -1;
  }

  void build(int l = 1, int r = n, int rt = 1) {
    cov[rt] = -1;
    if (l == r) {
      a[rt][0] = a[rt][1] = 0;
      a[rt][f[l] - '0'] = 1;
      return ;
    }
    int m = (l + r) / 2;
    build(lson);
    build(rson);
    pushup(rt);
  }

  int query(int L, int R, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      return a[rt][0];
    }
    int m = (l + r) / 2;
    pushdown(rt, m - l + 1, r - m);
    int ans = 0;
    if (L <= m) ans += query(L, R, lson);
    if (R > m) ans += query(L, R, rson);
    return ans;
  }

  void update(int L, int R, int x, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      cov[rt] = x;
      a[rt][0] = a[rt][1] = 0;
      a[rt][x] = r - l + 1;
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt, m - l + 1, r - m);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
  }

  bool check(int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      // dbg(l, a[rt][0], a[rt][1]);
      return a[rt][s[l] - '0'] == 1;
    }
    int m = (l + r) / 2;
    pushdown(rt, m - l + 1, r - m);
    return check(lson) && check(rson);
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &q);
    scanf("%s%s", s + 1, f + 1);
    for (int i = 1; i <= q; i++) {
      scanf("%d%d", ql + i, qr + i);
    }
    SegT::build();
    bool flag = true;
    for (int i = q; i >= 1; i--) {
      int sum0 = SegT::query(ql[i], qr[i]);
      int len = qr[i] - ql[i] + 1;
      // dbg(len, sum0);
      if (sum0 + sum0 < len) {
        SegT::update(ql[i], qr[i], 1);
        // dbg(i, 1);
      } else if (len - sum0 + len - sum0 < len) {
        SegT::update(ql[i], qr[i], 0);
        // dbg(i, 0);
      } else {
        flag = false;
        break;
      }
    }
    // dbg(SegT::query(1, n));
    flag &= SegT::check();
    puts(flag ? "YES" : "NO");
  }
  return 0;
}