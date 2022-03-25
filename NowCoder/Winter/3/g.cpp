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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

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
inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}
inline int inv(int x) {
  return qpow(x, mod - 2);
}

int n, q, ans;
char s[maxn];

struct BIT {
  int a[maxn], sum = 0;
  void update(int i, int x) {
    sum = add(sum, x);
    for (; i < maxn; i += i & -i) a[i] = add(a[i], x);
  }
  int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r = add(r, a[i]);
    return r;
  }
} f, g;

int main() {
  scanf("%d%s", &n, s + 1);
  for (int i = 1; i <= n; i++) {
    if (s[i] == '1') {
      f.update(i, i);
      g.update(i, 1);
    }
  }
  for (int i = 1; i <= n; i++) {
    if (s[i] == '1') {
      int sum = sub(mul(g.query(i - 1), i), f.query(i - 1));
      ans = add(ans, sum);
    }
  }
  printf("%d\n", ans);
  scanf("%d", &q);
  while (q--) {
    int op, pos; scanf("%d%d", &op, &pos);
    if (op == 1) {
      int s1 = sub(mul(g.query(pos - 1), pos), f.query(pos - 1));
      ans = add(ans, s1);
      int s2 = sub(sub(f.sum, f.query(pos)), mul(pos, sub(g.sum, g.query(pos))));
      ans = add(ans, s2);
      f.update(pos, pos);
      g.update(pos, 1);
    } else if (op == 2) {
      int s1 = sub(mul(g.query(pos - 1), pos), f.query(pos - 1));
      ans = sub(ans, s1);
      int s2 = sub(sub(f.sum, f.query(pos)), mul(pos, sub(g.sum, g.query(pos))));
      ans = sub(ans, s2);
      f.update(pos, mod - pos);
      g.update(pos, mod - 1);
    }
    printf("%d\n", ans);
  }
  return 0;
}