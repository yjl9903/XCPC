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

int n, a[maxn], b[maxn], ord[maxn];
ll pre[maxn];

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  ll a[maxn << 2], tag[maxn << 2];
  void build(int l = 1, int r = (int)1e5 + 1, int rt = 1) {
    tag[rt] = a[rt] = 0;
    if (l == r) {
      return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
  }
  void add(int rt, ll x) {
    a[rt] += x; tag[rt] += x;
  }
  void pushdown(int rt) {
    add(rt << 1, tag[rt]);
    add(rt << 1 | 1, tag[rt]);
    tag[rt] = 0;
  }
  void update(int L, int R, ll x, int l = 1, int r = (int)1e5 + 1, int rt = 1) {
    if (L <= l && r <= R) {
      add(rt, x); return ;
    }
    int m = (l + r) / 2;
    pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    a[rt] = max(a[rt << 1], a[rt << 1 | 1]);
  }
  ll query(int L, int R, int l = 1, int r = (int)1e5 + 1, int rt = 1) {
    if (L <= l && r <= R) {
      return a[rt];
    }
    int m = (l + r) / 2;
    pushdown(rt);
    ll ans = -(ll)1e18;
    if (L <= m) ans = query(L, R, lson);
    if (R > m) ans = max(ans, query(L, R, rson));
    return ans;
  }
}

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    pre[0] = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      pre[i] = pre[i - 1] + a[i];
      ord[i] = i;
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", b + i);
      if (i > 1) {
        b[i] = min(b[i], b[i - 1]);
      }
    }
    SegT::build();
    
  }
  return 0;
}