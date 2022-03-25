#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 250000 + 5;

int n, k;
vector<PII> bag[maxn];
multiset<int> cPos[maxn];

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  int a[maxn << 3], tag[maxn << 3];
  void build(int l = 1, int r = 500000, int rt = 1) {
    tag[rt] = a[rt] = 0;
    if (l == r) return ;
    int m = (l + r) / 2;
    build(lson); build(rson);
  }
  void pushup(int rt) {
    a[rt] = max(a[rt << 1], a[rt << 1 | 1]);
  }
  void apply(int rt, int x) {
    a[rt] += x; tag[rt] += x;
  }
  void pushdown(int rt) {
    if (tag[rt] == 0) return ;
    apply(rt << 1, tag[rt]);
    apply(rt << 1 | 1, tag[rt]);
    tag[rt] = 0;
  }
  void upadte(int L, int R, int x, int l = 1, int r = 500000, int rt = 1) {
    if (L <= l && r <= R) {
      apply(rt, x);
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt);
    if (L <= m) upadte(L, R, x, lson);
    if (R > m) upadte(L, R, x, rson);
    pushup(rt);
  }
  bool check() {
    return a[1] == k;
  }
}

bool check(int R) {
  SegT::build();
  for (int i = 1; i <= k; i++) {
    cPos[i].clear();
  }
  auto add = [&](int y, int c) {
    int l = y, r = y + R;
    auto it = cPos[c].lower_bound(y);
    if (it != cPos[c].end()) {
      r = min(r, *it - 1);
    }
    if (it != cPos[c].begin()) {
      it--;
      l = max(l, *it + R + 1);
    }
    if (l <= r) {
      SegT::upadte(l, r, 1);
    }
    cPos[c].insert(y);
  };
  auto del = [&](int y, int c) {
    int l = y, r = y + R;
    cPos[c].erase(cPos[c].find(y));
    auto it = cPos[c].lower_bound(y);
    if (it != cPos[c].end()) {
      r = min(r, *it - 1);
    }
    if (it != cPos[c].begin()) {
      it--;
      l = max(l, *it + R + 1);
    }
    if (l <= r) {
      SegT::upadte(l, r, -1);
    }
  };
  for (int i = 1; i < R; i++) {
    for (auto& x: bag[i]) {
      add(x.first, x.second);
    }
  }
  for (int i = R; i < maxn; i++) {
    for (auto& x: bag[i]) {
      add(x.first, x.second);
    }
    if (SegT::check()) return true;
    for (auto& x: bag[i - R]) {
      del(x.first, x.second);
    }
  }
  return false;
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    int x, y, c;
    scanf("%d%d%d", &x, &y, &c);
    bag[x].emplace_back(y, c);
  }
  int l = 0, r = 250000, ans = -1;
  while (l <= r) {
    int m = (l + r) / 2;
    if (check(m)) {
      ans = m;
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  assert(ans != -1);
  printf("%d\n", ans);
  return 0;
}