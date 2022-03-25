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
const int maxn = 300000 + 5;

int n, q, a[maxn];
vector<int> bag[maxn];

int count(int x, int l, int r) {
  return upper_bound(bag[x].begin(), bag[x].end(), r) - lower_bound(bag[x].begin(), bag[x].end(), l);
}

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  struct Info {
    int x, cnt;

    Info operator + (const Info& rhs) const {
      if (x == rhs.x) {
        return { x, cnt + rhs.cnt };
      } else if (cnt < rhs.cnt) {
        return { rhs.x, rhs.cnt - cnt };
      } else {
        return { x, cnt - rhs.cnt };
      }
    }
  } a[maxn << 2];

  void build(int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      a[rt] = { ::a[l], 1 };
      return ;
    }
    int m = (l + r) / 2;
    build(lson);
    build(rson);
    a[rt] = a[rt << 1] + a[rt << 1 | 1];
  }

  Info query(int L, int R, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      return a[rt];
    }
    int m = (l + r) / 2;
    if (R <= m) return query(L, R, lson);
    else if (L > m) return query(L, R, rson);
    else return query(L, R, lson) + query(L, R, rson);
  }
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    bag[a[i]].push_back(i);
  }
  SegT::build();
  for (int i = 1; i <= q; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    auto res = SegT::query(l, r);
    int sum = r - l + 1;
    int cnt = count(res.x, l, r);
    printf("%d\n", max(1, 2 * cnt - sum));
  }
  return 0;
}