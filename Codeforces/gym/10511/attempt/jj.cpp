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
#include <cstdlib>
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
const int maxn = 200000 + 5;

int n, xx[maxn], yy[maxn];
double a[maxn], B;

double check(double k) {
  for (int i = 1; i <= n; i++) {
    a[i] = xx[i] - k * yy[i];
  }
  sort(a + 1, a + 1 + n);
  double ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += abs(a[i] - a[n / 2 + 1]);
  }
  double res = 0;
  for (int i = 1; i <= n; i++) {
    res += abs(a[i] - a[n / 2]);
  }
  if (ans < res) {
    B = a[n / 2 + 1];
    return ans;
  } else {
    B = a[n / 2];
    return res;
  }
}

double cal(double k, double b) {
  double ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += abs(k * yy[i] + b - xx[i]);
  }
  return ans;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", xx + i);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", yy + i);
  }

  double ansx = 0, ansy = 0;
  double ans = inf;
  {
    double l = 0.0, r = 1e4;
    for (int i = 0; i < 1000000; i++) {
      double ml = l + (r - l) / 3;
      double mr = r - (r - l) / 3;
      double r1 = check(ml);
      double r2 = check(mr);
      if (r1 < r2) {
        r = mr;
      } else {
        l = ml;
      }
    }
    ans = check(l);
    ansx = l;
    ansy = B;
  }

  const double delta = 0.9998;
  const double eps = 1e-17;

  double x = ansx, y = ansy, t = 4000;
  while (t > eps) {
    double tx = x + ((rand() << 1) - RAND_MAX) * t;
    double ty = y + ((rand() << 1) - RAND_MAX) * t;
    double now = cal(tx, ty), d = now - ans;
    if (d < 0) {
      x = tx;
      y = ty;
      ansx = tx;
      ansy = ty;
      ans = now;
    } else if (exp(-d / t) * RAND_MAX > rand()) {
      x = tx, y = ty;
    }
    t *= delta;
  }
  printf("%.12lf %.12lf %.12lf\n", ans, ansx, ansy);
  return 0;
}
