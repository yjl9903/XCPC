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

struct BIT {
  static const int R = 1 << 21;
  int a[R];
  inline int lowbit(int x) { return x & -x; }
  void insert(int i, int x = 1) {
    for (; i < R; i += lowbit(i)) a[i] += x;
  }
  void del(int i) {
    for (; i < R; i += lowbit(i)) a[i] = 0;
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

int n, w, a[maxn];

int main() {
  while (scanf("%d%d", &n, &w) == 2) {
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      f.del(a[i]);
    }
    for (int i = 1; i < w; i++) {
      f.insert(a[i]);
    }
    for (int i = w; i <= n; i++) {
      f.insert(a[i]);
      printf("%d ", f.findx(w - 2));
      f.insert(a[i - w + 1], -1);
    }
    puts("");
  }
  return 0;
}