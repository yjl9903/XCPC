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

struct Node {
  int A, B;

  bool operator < (const Node& rhs) const {
    return A - B > rhs.A - rhs.B;
  }
} a[maxn];

int n, L, ok[maxn];
ll c[maxn], pre[maxn], lim[maxn];

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  ll a[maxn << 2], tag[maxn << 2];
  void pushup(int rt) {
    a[rt] = min(a[rt << 1], a[rt << 1 | 1]);
  }
  void pushdown(int rt) {
    if (tag[rt]) {
      ll t = tag[rt];
      a[rt << 1] += t;
      tag[rt << 1] += t;
      a[rt << 1 | 1] += t;
      tag[rt << 1 | 1] += t;
      tag[rt] = 0;
    }
  }
  void build(int l = 2, int r = n, int rt = 1) {
    if (l == r) {
      a[rt] = pre[l] - c[l - 1] - pre[1];
      return ;
    }
    int m = (l + r) / 2;
    build(lson);
    build(rson);
    pushup(rt);
  }

  void update(int L, int R, ll x, int l = 2, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      a[rt] += x;
      tag[rt] += x;
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
  }

  ll query(int L, int R, int l = 2, int r = n, int rt = 1) {
    if (L <= l && r <= R) return a[rt];
    int m = (l + r) / 2;
    pushdown(rt);
    if (R <= m) {
      return query(L, R, lson);
    } else if (L > m) {
      return query(L, R, rson);
    } else {
      return min(query(L, R, lson), query(L, R, rson));
    }
  }
}

int main() {
  scanf("%d%d", &n, &L);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].A, &a[i].B);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%lld", c + i);
    c[i] += c[i - 1];
  }
  sort(a + 1, a + 1 + n);
  int Lim = n + 1;
  for (int i = 1; i <= n; i++) {
    if (a[i].A - a[i].B < 0) {
      Lim = i;
      break;
    }
  }
  for (int i = 1; i <= n; i++) {
    pre[i] = pre[i - 1] + a[i].A - a[i].B;
    ok[i] = ok[i - 1] + (pre[i] > c[i]);
  }
  SegT::build();
  int ans = -1;
  auto upd = [&](int val) {
    dbg(val);
    if (ans == -1) ans = val;
    else if (ans > val) ans = val;
  };
  for (int i = 1; i <= n; i++) {
    dbg(i);
    {
      int id = lower_bound(pre + 1, pre + Lim, L - a[i].A) - pre;
      if (id < i && ok[id] == id) {
        upd(id + 1);
      }
    }
    if (i < n) {
      int id = lower_bound(pre + 1, pre + Lim, L - a[i].B) - pre;
      if (i <= id && id <= n && ok[i - 1] == i - 1) {
        if (id == i || SegT::query(i + 1, id) > 0) {
          upd(id);
        }
      }
      ll val = 1ll * a[i].A - a[i].B;
      val -= 1ll * a[i + 1].A - a[i + 1].B;
      SegT::update(i + 1, n, val);
    }
  }
  printf("%d\n", ans);
  return 0;
}