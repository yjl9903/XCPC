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
const ll inf = 1ll << 60;
const int maxn = 300000 + 5;

int n, q, a[maxn];

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  struct Node {
    ll val[2][2];

    Node(int x = 0) {
      val[0][0] = 0;
      val[0][1] = x;
      val[1][0] = -x;
      val[1][1] = 0;
    }

    Node operator+ (const Node& b) const {
      Node r;
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          r.val[i][j] = -inf;
          for (int k = 0; k < 2; k++) {
            r.val[i][j] = max(r.val[i][j], val[i][k] + b.val[k][j]);
          }
        }
      }
      return r;
    }
  } a[maxn << 2];

  void build(int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      a[rt] = Node(::a[l]);
      return ;
    }
    int m = (l + r) / 2;
    build(lson);
    build(rson);
    a[rt] = a[rt << 1] + a[rt << 1 | 1];
    // dbg(l, r, a[rt].val[0], a[rt].val[1]);
  }
  void update(int i, int x, int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      a[rt] = Node(x);
      return ;
    }
    int m = (l + r) / 2;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    a[rt] = a[rt << 1] + a[rt << 1 | 1];
  }

  ll ans() {
    ll ans = 0;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        ans = max(ans, a[1].val[i][j]);
      }
    }
    return ans;
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    SegT::build();
    printf("%I64d\n", SegT::ans());
    while (q--) {
      int L, R;
      scanf("%d%d", &L, &R);
      swap(a[L], a[R]);
      SegT::update(L, a[L]);
      SegT::update(R, a[R]);
      printf("%I64d\n", SegT::ans());
    }
  }
  return 0;
}