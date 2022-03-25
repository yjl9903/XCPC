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
const int maxn = 1000000 + 5;

struct BIT {
  static const int R = 1 << 21;
  int a[R];
  inline int lowbit(int x) { return x & -x; }
  void update(int i, int x) {
    for (; i < R; i += lowbit(i)) a[i] += x;
  }
  void ins(int i) {
    update(i, 1);
  }
  void del(int i) {
    update(i, -1);
  }
  int findx(int p, int rk) {
    // if (p > R) return -1;
    if (p & 1) {
      // if (p + (a[p] < rk) > R) return -1;
      return p + (a[p] < rk);
    } else {
      if (rk > a[p]) return findx(p + lowbit(p) / 2, rk - a[p]);
      else return findx(p - lowbit(p) / 2, rk);
    }
  }
  int findx(int rk) {
    return findx(R >> 1, rk);
  }
} f;

int n, q;

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    int x; scanf("%d", &x);
    f.ins(x);
  }
  int cnt = n;
  for (int i = 1; i <= q; i++) {
    int x; scanf("%d", &x);
    if (x > 0) {
      f.ins(x); cnt++;
    } else {
      int tag = f.findx(-x);
      f.del(tag); cnt--;
    }
  }
  if (!cnt) {
    puts("0");
  } else {
    printf("%d\n", f.findx(1));
  }
  return 0;
}