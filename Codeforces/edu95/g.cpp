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
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

int n, a[maxn];
vector<int> bag[maxn];
vector<tuple<int,int,int> > upd[maxn];

void push(int l1, int r1, int l2, int r2) {
  upd[l1].emplace_back(l2, r2, 1);
  upd[r1 + 1].emplace_back(l2, r2, -1);
  // dbg(l1, r1, l2, r2);
}

namespace SegT {
  struct Node {
    int val, cnt;
    void clear() {
      val = 0;
      cnt = 0;
    }
    Node(int x = 0, int y = 0) {
      val = x;
      cnt = y;
    }
    Node operator + (const Node& b) const {
      if (val == b.val) return Node { val, cnt + b.cnt };
      else if (val > b.val) return Node { val, cnt };
      else return Node { b.val, b.cnt };
    }
    void operator += (const int& b) {
      val += b;
    }
  } b[maxn * 4];

  int tag[maxn * 4];
  void build(int l = 1, int r = n, int rt = 1) {
    b[rt].clear();
    tag[rt] = 0;
    if (l == r) {
      b[rt].cnt = 1; return ;   
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
  }
  void pushdown(int rt) {
    if (!tag[rt]) return ;
    int& t = tag[rt];
    b[rt << 1] += t;
    tag[rt << 1] += t;
    b[rt << 1 | 1] += t;
    tag[rt << 1 | 1] += t;
    t = 0;
  }
  void update(int L, int R, int x, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      b[rt] += x;
      tag[rt] += x;
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    b[rt] = b[rt << 1] + b[rt << 1 | 1];
  }
  Node query(int L, int R, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      return b[rt];
    }
    int m = (l + r) / 2;
    pushdown(rt);
    if (L <= m && R > m) {
      return query(L, R, lson) + query(L, R, rson);
    } else if (R <= m) {
      return query(L, R, lson);
    } else {
      return query(L, R, rson);
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    bag[a[i]].push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    if (bag[i].empty()) {
      push(1, n, 1, n);
    } else {
      int l = 1;
      int r = bag[i].front() - 1;
      if (l <= r) {
        push(l, r, l, r);
      }
      for (int j = 0; j + 1 <= (int)bag[i].size(); j++) {
        int l = bag[i][j] + 1;
        int r = j + 1 == bag[i].size() ? n : bag[i][j + 1] - 1;
        if (l <= r) {
          push(l, r, l, r);
        }
      }
      for (int j = 0; j + 2 < (int)bag[i].size(); j++) {
        int l1 = bag[i][j + 2];
        int r1 = j + 3 == bag[i].size() ? n : bag[i][j + 3] - 1;
        int l2 = j == 0 ? 1 : bag[i][j - 1] + 1;
        int r2 = bag[i][j];
        push(l1, r1, l2, r2);
      }
    }
  }
  SegT::build();
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    for (auto x: upd[i]) {
      int l, r, v;
      tie(l, r, v) = x;
      SegT::update(l, r, v);
    }
    auto res = SegT::query(1, i);
    // dbg(res.val, res.cnt);
    // dbg(SegT::b[1].val, SegT::b[1].cnt);
    if (res.val == n) {
      ans += res.cnt;
    }
  }
  printf("%I64d\n", ans);
  return 0;
}