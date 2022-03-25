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
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
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
using ll = long long;
using PII = pair<int,int>;
using TIII = tuple<int,int,int>;
const int mod = 256;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

int n, m, q;
int tot, val[maxn], beg[maxn], siz[maxn], ans[maxn];
bool isQ[maxn];

namespace SegTCov {
  TIII Empty = TIII { -1, -1, -1 };
  TIII a[maxn << 2], tag[maxn << 2];
  void build(int l = 1, int r = n, int rt = 1) {
    a[rt] = Empty;
    tag[rt] = Empty;
    if (l == r) return ;
    int m = (l + r) / 2;
    build(lson); build(rson);
  }
  void pushdown(int rt) {
    if (tag[rt] == Empty) return ;
    a[rt << 1] = tag[rt];
    a[rt << 1 | 1] = tag[rt];
    tag[rt << 1] = tag[rt];
    tag[rt << 1 | 1] = tag[rt];
    tag[rt] = Empty;
  }
  void update(int L, int R, TIII x, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      a[rt] = x;
      tag[rt] = x;
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
  }
  TIII query(int x, int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      return a[rt];
    }
    int m = (l + r) / 2;
    pushdown(rt);
    if (x <= m) return query(x, lson);
    else return query(x, rson);
  }
}

namespace SegTAdd {
  void add(int& x, int y) {
    x = (x + y) % mod;
  }

  int a[maxn << 2], tag[maxn << 2];
  void pushdown(int rt) {
    if (tag[rt] == 0) return ;
    int t = tag[rt];
    add(a[rt << 1], t);
    add(a[rt << 1 | 1], t);
    add(tag[rt << 1], t);
    add(tag[rt << 1 | 1], t);
    tag[rt] = 0;
  }
  void build(int l = 1, int r = tot, int rt = 1) {
    tag[rt] = 0;
    if (l == r) {
      a[rt] = val[l];
      return ;
    }
    int m = (l + r) / 2;
    build(lson);
    build(rson);
  }
  void update(int L, int R, int l = 1, int r = tot, int rt = 1) {
    if (L <= l && r <= R) {
      tag[rt]++;
      add(a[rt], 1);
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt);
    if (L <= m) update(L, R, lson);
    if (R > m) update(L, R, rson);
  }
  int query(int x, int l = 1, int r = tot, int rt = 1) {
    if (l == r) return a[rt];
    int m = (l + r) / 2;
    pushdown(rt);
    if (x <= m) return query(x, lson);
    else return query(x, rson);
  }
}

vector<PII> qry[maxn];

int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= m; i++) {
    scanf("%d", siz + i);
    beg[i] = tot + 1;
    for (int j = 0; j < siz[i]; j++) {
      tot++;
      scanf("%d", val + tot);
    }
  }

  vector<TIII> upd;
  SegTCov::build();
  SegTAdd::build();
  for (int i = 1; i <= q; i++) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int x, p;
      scanf("%d%d", &x, &p);
      // cov: p ~ p + siz[x] - 1, time
      SegTCov::update(p, p + siz[x] - 1, TIII { x, p, i });
    } else if (op == 2) {
      isQ[i] = true;
      int p;
      scanf("%d", &p);
      // query: (x th data, start, time)
      auto record = SegTCov::query(p);
      if (get<2>(record) == -1) {
        ans[i] = 0;
      } else {
        int pos = beg[get<0>(record)] + (p - get<1>(record) + 1) - 1;
        qry[get<2>(record)].emplace_back(pos, i);
      }
    } else if (op == 3) {
      int x, l, r;
      scanf("%d%d%d", &x, &l, &r);
      int L = beg[x] + l - 1, R = beg[x] + r - 1;
      // add: (L, R) => + 1
      upd.emplace_back(i, L, R);
    }
  }

  sort(begin(upd), end(upd));
  for (int i = 1, p = 0; i <= q; i++) {
    if (p < (int)upd.size() && get<0>(upd[p]) == i) {
      SegTAdd::update(get<1>(upd[p]), get<2>(upd[p]));
      p++;
    }
    for (auto& x: qry[i]) {
      // dbg(i, x.first, x.second);
      ans[x.second] = SegTAdd::query(x.first);
    }
  }

  for (int i = 1; i <= q; i++) {
    if (isQ[i]) {
      printf("%d\n", ans[i]);
    }
  }
  return 0;
}