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
const ll inf = 1ll << 60;
const int maxn = 300000 + 5;

int n, m, a[maxn][2];
ll dp[maxn][2], ans[maxn];

struct SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  ll a[maxn << 2], tag[maxn << 2];
  void pushup(int rt) {
    a[rt] = max(a[rt << 1], a[rt << 1 | 1]);
  }
  void pushdown(int rt) {
    if (tag[rt] == 0) return ;
    ll t = tag[rt];

    a[rt << 1] += t;
    a[rt << 1 | 1] += t;
    tag[rt << 1] += t;
    tag[rt << 1 | 1] += t;

    tag[rt] = 0;
  }
  void build(int l = 0, int r = n, int rt = 1) {
    a[rt] = -inf;
    tag[rt] = 0;
    if (l == r) return ;
    int m = (l + r) / 2;
    build(lson);
    build(rson);
  }
  void update(int L, int R, ll x, int l = 0, int r = n, int rt = 1) {
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
  ll qmax() {
    return a[1];
  }
} f[2];

struct Seg {
  int tp, l, r, val;
} b[maxn];

vector<int> bag[maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i][0]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i][1]);
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d%d", &b[i].tp, &b[i].l, &b[i].r, &b[i].val);
    b[i].tp--;
    bag[b[i].r].push_back(i);
  }

  f[0].build();
  f[1].build();

  for (int i = 1; i <= n; i++) {
    f[0].update(1, i, a[i][0]);
    f[0].update(i, i, inf);
    f[0].update(i, i, ans[i - 1]);
    f[1].update(1, i, a[i][1]);
    f[1].update(i, i, inf);
    f[1].update(i, i, ans[i - 1]);

    for (auto id: bag[i]) {
      int tp = b[id].tp;
      int l = b[id].l;
      f[tp].update(1, l, b[id].val);
    }

    ans[i] = max(f[0].qmax(), f[1].qmax());
  }

  printf("%lld\n", ans[n]);
  return 0;
}