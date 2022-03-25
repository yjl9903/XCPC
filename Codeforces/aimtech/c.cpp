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
const int maxn = 100000 + 5;

int n, q, a[maxn];
ll b[maxn];

void update(int i, int x) {
  for (; i < maxn; i += i & -i) b[i] += x;
}
ll query(int i) {
  ll r = 0;
  for (; i; i -= i & -i) r += b[i];
  return r;
}
ll query(int l, int r) {
  return query(r) - query(l - 1);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &q);
    int op;
    while (q--) {
      scanf("%d", &op);
      if (op == 1) {
        int x, y; scanf("%d%d", &x, &y);
        update(x, -a[x]);
        a[x] = y;
        update(x, a[x]);
      } else if (op == 2) {
        int l, r; scanf("%d%d", &l, &r);
        printf("%I64d\n", query(l, r));
      }
    }
  }
  return 0;
}