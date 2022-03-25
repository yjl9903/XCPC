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
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, T, a[maxn];

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  struct Node {
    int val, pos;

    Node operator + (const Node& rhs) const {
      if (val > rhs.val) {
        return { val, pos };
      } else if (val < rhs.val) {
        return { rhs.val, rhs.pos };
      } else if (pos < rhs.pos) {
        return { val, pos };
      } else {
        return { rhs.val, rhs.pos };
      }
    }
  } a[maxn << 2];
  int tag[maxn << 2];

  void build(int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      a[rt].val = ::a[l];
      a[rt].pos = l;
      return ;
    }
    int m = (l + r) / 2;
    build(lson);
    build(rson);
    a[rt] = a[rt << 1] + a[rt << 1 | 1];
  }

  void pushdown(int rt) {
    if (tag[rt] == 0) return ;
    int t = tag[rt];
    tag[rt << 1] += t;
    tag[rt << 1 | 1] += t;
    a[rt << 1].val += t;
    a[rt << 1 | 1].val += t;
    tag[rt] = 0;
  }

  void update(int i, int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      a[rt].val = ::a[l];
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt);
    if (i <= m) update(i, lson);
    else update(i, rson);
    a[rt] = a[rt << 1] + a[rt << 1 | 1];
  }
}

int cnt[maxn];

int main() {
  scanf("%d%d", &n, &T);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  SegT::build();
  for (int i = 1; i <= T; i++) {
    auto cur = SegT::a[1];
    cnt[cur.pos]++;
    SegT::tag[1]++;
    SegT::update(cur.pos);
  }
  for (int i = 1; i <= n; i++) {
    printf("%d%c", cnt[i], " \n"[i == n]);
  }
  return 0;
}