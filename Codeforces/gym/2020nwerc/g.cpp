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
const int maxn = 5000 + 5;

int n, r, m, t[maxn], d[maxn];
double p[maxn];

double f[maxn][maxn];
bool check(double x) {
  for (int j = 0; j < r - n; j++) {
    f[m + 1][j] = 0.0;
  }
  for (int i = m; i >= 1; i--) {
    for (int j = 0; j < r - n; j++) {
      double cur = p[i] * (t[i + 1] - t[i] + f[i + 1][j]);
      double waste = x;
      if (j + d[i] < r - n) {
        waste = min(waste, t[i + 1] - t[i] + d[i] + f[i + 1][j + d[i]]);
      }
      cur += (1.0 - p[i]) * waste;
      f[i][j] = cur;
    }
  }
  return f[1][0] + t[1] <= x;
}

int main() {
  scanf("%d%d%d", &n, &r, &m);
  for (int i = 1; i <= m; i++) {
    scanf("%d%lf%d", t + i, p + i, d + i);
  }
  t[m + 1] = n;
  double l = 0.0, r = 1e18;
  for (int i = 1; i <= 150; i++) {
    double m = (l + r) / 2.0;
    if (check(m)) {
      r = m;
    } else {
      l = m;
    }
  }
  printf("%.10lf\n", l);
  return 0;
}