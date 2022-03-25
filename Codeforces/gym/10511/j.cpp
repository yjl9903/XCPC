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
  double ans = inf;
  double ansk = inf, ansb = inf;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      double k = 1.0 * (xx[i] - xx[j]) / (yy[i] - yy[j]);
      double b = 1.0 * (xx[j] * yy[i] - xx[i] * yy[j]) / (yy[i] - yy[j]);
      double r = cal(k, b);
      if (r < ans) {
        ans = r;
        ansk = k;
        ansb = b;
      }
    }
  }
  printf("%.12lf %.12lf %.12lf\n", ans, ansk, ansb);
  return 0;
}
