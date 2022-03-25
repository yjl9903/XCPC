#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
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

int n, k1, k2, k3, a[maxn], bel[maxn];

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1
  int a[maxn << 2], tag[maxn << 2];
  void pushdown(int rt) {
    if (!tag[rt]) return ;
    int t = tag[rt];
    a[rt << 1] += t; tag[rt << 1] += t;
    a[rt << 1 | 1] += t; tag[rt << 1 | 1] += t;
    tag[rt] = 0;
  }
  void update(int L, int R, int x, int l = 1, int r = n + 1, int rt = 1) {
    if (L <= l && r <= R) {
      a[rt] += x; tag[rt] += x;
      return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    a[rt] = min(a[rt << 1], a[rt << 1 | 1]);
  }
  int query(int L, int R, int l = 1, int r = n + 1, int rt = 1) {
    if (L <= l && r <= R) return a[rt];
    int m = (l + r) / 2, ans = inf; pushdown(rt);
    if (L <= m) ans = query(L, R, lson);
    if (R > m) ans = min(ans, query(L, R, rson));
    return ans;
  }
}
using SegT::update;
using SegT::query;

int main() {
  scanf("%d%d%d", &k1, &k2, &k3);
  n = k1 + k2 + k3;
  for (int i = 1, x; i <= k1; i++) {
    scanf("%d", &x); bel[x] = 1;
  }
  for (int i = 1, x; i <= k2; i++) {
    scanf("%d", &x); bel[x] = 2;
  }
  for (int i = 1, x; i <= k3; i++) {
    scanf("%d", &x); bel[x] = 3;
  }
  int pre = 0, rest = k1, ans = inf;
  for (int i = 1; i <= n; i++) {
    if (bel[i] == 2) {
      update(1, i, 1);
    } else if (bel[i] == 3) {
      update(i + 1, n + 1, 1);
    }
  }
  for (int i = 0; i <= n; i++) {
    if (bel[i] == 1) {
      rest--;
    } else if (bel[i] == 2) {
      pre++;
    } else if (bel[i] == 3) {
      pre++;
      update(i + 1, n + 1, -1);
    }
    ans = min(ans, pre + rest + query(i + 1, n + 1));
  }
  cout << ans;
  return 0;
}