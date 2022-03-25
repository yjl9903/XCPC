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
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
  return 1ll * x * y % mod;
}

int n, q, k[maxn], b[maxn];

struct Info {
  int k, b;
  Info(int a = 0, int b = 0): k(a), b(b) {}
  Info operator + (const Info& b) {
    return Info(mul(b.k, k), add(mul(b.k, this->b), b.b));
  }
} a[maxn << 2];

void build(int l = 1, int r = n, int rt = 1) {
  if (l == r) {
    a[rt].k = k[l]; a[rt].b = b[l];
    return ;
  }
  int m = (l + r) / 2;
  build(lson); build(rson);
  a[rt] = a[rt << 1] + a[rt << 1 | 1];
}
void update(int i, int l = 1, int r = n, int rt = 1) {
  if (l == r) {
    scanf("%d%d", &a[rt].k, &a[rt].b);
    return ;
  }
  int m = (l + r) / 2;
  if (i <= m) update(i, lson);
  else update(i, rson);
  a[rt] = a[rt << 1] + a[rt << 1 | 1];
}
Info query(int L, int R, int l = 1, int r = n, int rt = 1) {
  if (L <= l && r <= R) return a[rt];
  int m = (l + r) / 2;
  if (R <= m) return query(L, R, lson);
  if (L > m) return query(L, R, rson);
  return query(L, R, lson) + query(L, R, rson);
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) scanf("%d", k + i);
  for (int i = 1; i <= n; i++) scanf("%d", b + i);
  build();
  for (int i = 1, op; i <= q; i++) {
    scanf("%d", &op);
    if (op == 1) {
      int i; scanf("%d", &i);
      update(i);
    } else if (op == 2) {
      int l, r; scanf("%d%d", &l, &r);
      auto x = query(l, r);
      printf("%d\n", add(x.k, x.b));
    }
  }
  return 0;
}