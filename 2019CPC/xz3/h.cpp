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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, q, a[maxn];

namespace PSegT {
  #define lson l, m, ls[rt]
  #define rson m + 1, r, rs[rt]
  int tot, root[maxn], ls[maxn * 150], rs[maxn * 150];
  ll cnt[maxn * 150];

  vector<int> nodes;
  int node() {
    if (nodes.empty()) return ++tot;
    int r = nodes.back(); nodes.pop_back();
    return r;
  }
  void del(int& x) {
    ls[x] = rs[x] = cnt[x] = 0;
    nodes.push_back(x); x = 0;
  }
  
  void update(int i, int x, int l, int r, int& rt) {
    if (!rt) rt = node();
    cnt[rt] += x;
    if (l == r) {
      if (!cnt[rt]) del(rt), rt = 0;
      return ;
    }
    int m = (l + r) / 2;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    if (!cnt[rt]) del(rt), rt = 0;
  }

  vector<int> L, R;
  ll query(int i, int l, int r, int rt) {
    if (l == r) {
      ll sum = 0;
      for (int x: L) sum -= cnt[x];
      for (int x: R) sum += cnt[x];
      return sum;
    }
    int m = (l + r) / 2;
    if (i <= m) {
      for (int& x: L) x = ls[x];
      for (int& x: R) x = ls[x];
      return query(i, l, m, 1);
    } else {
      ll sum = 0;
      for (int& x: L) sum -= cnt[ls[x]], x = rs[x];
      for (int& x: R) sum += cnt[ls[x]], x = rs[x];
      return sum + query(i, m + 1, r, 1);
    }
  }
  inline void update(int i, int pos, int val) {
    for (; i <= n; i += i & -i) update(pos, val, 1, 2e5, root[i]);
  }
  inline ll query(int l, int r, int k) {
    L.clear(); R.clear();
    for (int i = l - 1; i; i -= i & -i) L.push_back(root[i]);
    for (int i = r; i; i -= i & -i) R.push_back(root[i]);
    return query(k, 1, 2e5, 1);
  }
}

ll solve(int l, int r) {
  auto query = [&](ll k) -> ll {
    if (k >= (int)2e5) k = 2e5;
    return PSegT::query(l, r, (int)k);
  };
  for (ll i = 1, nxt = 0; ; i = nxt + 1) {
    nxt = query(i);
    if (nxt < i) return i;
  }
  assert(0);
  return -1;
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    PSegT::update(i, a[i], a[i]);
  }
  int op, x, y;
  while (q--) {
    scanf("%d%d%d", &op, &x, &y);
    if (op == 1) {
      PSegT::update(x, a[x], -a[x]);
      a[x] = y;
      PSegT::update(x, a[x], a[x]);
    } else if (op == 2) {
      printf("%lld\n", solve(x, y));
    }
  }
  return 0;
}