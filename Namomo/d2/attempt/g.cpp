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
using PDD = pair<double,double>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;
const double eps = 1e-3;

bool le(long double x, long double y) {
  if (abs(x - y) < eps) {
    return true;
  } else {
    return x < y;
  }
}

int n;
ll d, a[maxn];

bool check(long double x) {
  long double l = 1.0 * a[1] - x + d, r = 1.0 * a[1] + x + d;
  // dbg(l, r);
  for (int i = 2; i <= n; i++) {
    l = max(l, a[i] - x);
    r = min(r, a[i] + x);
    // dbg(l, r);
    if (!le(l, r)) return false;
    l += d;
    r += d;
  }
  return true;
}

bool check2(long double x) {
  long double l = 1.0 * a[1] - x - d, r = 1.0 * a[1] + x - d;
  for (int i = 2; i <= n; i++) {
    l = max(l, a[i] - x);
    r = min(r, a[i] + x);
    // dbg(l, r);
    if (!le(l, r)) return false;
    l -= d;
    r -= d;
  }
  return true;
}

int main() {
  scanf("%d%lld", &n, &d);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", a + i);
  }
  // sort(a + 1, a + 1 + n);
  long double l = 0.0, r = 1e16;
  // for (int i = 0; i < 70; i++) {
  while (r - l > eps) {
    long double m = (l + r) / 2.0;
    if (check(m) || check2(m)) {
      r = m;
    } else {
      l = m;
    }
  }
  // printf("%.1Lf\n", (l + r) / 2.0);
  // printf("%.1Lf %.1Lf\n", l, r);
  printf("%.1Lf\n", l);
  return 0;
}