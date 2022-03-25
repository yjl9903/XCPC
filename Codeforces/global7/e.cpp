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
const int maxn = 300000 + 5;

int n, p[maxn], q[maxn], pos[maxn];

struct SegTree {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1
  function<ll(ll,ll)> merge = [](ll a, ll b) { return min(a, b); };
  ll a[maxn << 2];
  int tag[maxn << 2];
  void build(int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      a[rt] = 0; return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
    a[rt] = merge(a[rt << 1], a[rt << 1 | 1]);
  }
  void push(int rt, int x) {
    a[rt] += x; tag[rt] += x;
  }
  void pushdown(int rt) {
    if (!tag[rt]) return ;
    push(rt << 1, tag[rt]);
    push(rt << 1 | 1, tag[rt]);
    tag[rt] = 0;
  }
  void update(int L, int R, int x, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      push(rt, x); return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    a[rt] = merge(a[rt << 1], a[rt << 1 | 1]);
  }
  ll query(int L, int R, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) return a[rt];
    int m = (l + r) / 2; pushdown(rt);
    if (R <= m) return query(L, R, lson);
    if (L > m) return query(L, R, rson);
    return merge(query(L, R, lson), query(L, R, rson));
  }
} f;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", p + i);
    pos[p[i]] = i;
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", q + i);
  }
  int ans = n;
  auto check = [&]() {
    if (ans == 1) return false;
    f.update(1, pos[ans], -1);
    if (f.query(1, n) < 0) {
      f.update(1, pos[ans], 1);
      return false;
    }
    ans--;
    return true;
  };
  for (int i = 1; i <= n; i++) {
    printf("%d ", ans);
    f.update(1, q[i], 1);
    while (check());
  }
  return 0;
}