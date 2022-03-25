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
  #define dbg(args...) cout << #args << " -> ", err(args)
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
const int maxn = 200000 + 5;

int n, p[maxn], a[maxn], pos[maxn];

ll cost[maxn];
namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1
  ll mn[maxn << 2], tag[maxn << 2];
  void pushup(int rt) {
    mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
  }
  void pushdown(int rt) {
    if (!tag[rt]) return ;
    ll t = tag[rt];
    mn[rt << 1] += t;
    mn[rt << 1 | 1] += t;
    tag[rt << 1] += t;
    tag[rt << 1 | 1] += t;
    tag[rt] = 0;
  }
  void build(int l = 1, int r = n - 1, int rt = 1) {
    if (l == r) {
      mn[rt] = cost[l]; return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
    pushup(rt);
  }
  void update(int L, int R, int x, int l = 1, int r = n - 1, int rt = 1) {
    if (L <= l && r <= R) {
      mn[rt] += x; tag[rt] += x;
      return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
  }
  ll query() {
    return mn[1];
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", p + i); pos[p[i]] = i;
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  ll ans = 1e18, sum = 0;
  for (int i = 1; i < n; i++) {
    sum += a[i]; ans = min(ans, sum);
  }
  sum = 0;
  for (int i = n; i > 1; i--) {
    sum += a[i]; ans = min(ans, sum);
  }

  sum = a[pos[1]];
  for (int i = 1; i < n; i++) {
    if (p[i] > 1) {
      sum += a[i];
    } else if (p[i] <= 1) {
      sum -= a[i];
    }
    cost[i] = sum;
    ans = min(ans, sum);
    dbg(i, cost[i]);
  }
  SegT::build();

  for (int i = 2; i <= n; i++) {
    int x = pos[i];
    if (x > 1) {
      SegT::update(1, x - 1, a[x]);
    }
    if (x < n) {
      SegT::update(x, n - 1, -a[x]);
    }
    ans = min(ans, SegT::query());
  }

  cout << ans << endl;
  return 0;
}