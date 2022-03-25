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
const int inf = 1 << 30;
const int maxn = 100000 + 5;
 
struct BIT {
  static const int R = 1 << 21;
  int a[R];
  inline int lowbit(int x) { return x & -x; }
  void insert(int i, int x = 1) {
    for (; i < R; i += lowbit(i)) a[i] += x;
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
 
int n, m, ans[maxn], trans[maxn], temp[maxn];
 
void qpow(int k) {
  while (k) {
    if (k % 2) {
      for (int i = 1; i <= n; i++) temp[i] = ans[trans[i]];
      for (int i = 1; i <= n; i++) ans[i] = temp[i];
    }
    for (int i = 1; i <= n; i++) temp[i] = trans[trans[i]];
    for (int i = 1; i <= n; i++) trans[i] = temp[i];
    k >>= 1;
  }
}
 
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    ans[i] = i;
  }
  for (int i = 1, k, x; i <= m; i++) {
    scanf("%d%d", &k, &x);
    for (int i = 1; i <= n; i++) {
      f.insert(i);
    }
    int cur = k - 1;
    for (int i = 1, sz = n; i <= n; i++, sz--) {
      int tot = f.findx(cur + 1);
      // dbg(cur, tot);
      trans[i] = tot;
      f.insert(tot, -1);
      if (i == n) break;
      cur = (cur + k - 1) % (sz - 1);
    }
    qpow(x);
  }
  for (int i = 1; i <= n; i++) {
    printf("%d%c", ans[i], " \n"[i == n]);
  }
  return 0;
}