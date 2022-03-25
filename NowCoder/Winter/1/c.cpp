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

const double eps = 1e-7;

int sign(int x) {
  if (x == 0) return 0;
  return x > 0 ? 1 : -1;
}

struct Point {
  int x, y;
  Point(int x = 0, int y = 0): x(x), y(y) {}
  void read() {
    scanf("%d%d", &x, &y);
  }
} me, a[maxn];

int n, k;

int main() {
  me.read();
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    a[i].read();
  }

  bool ok = false;
  double ans = 0;

  // y-axis
  vector<double> v;
  for (int i = 1; i <= n; i++) {
    if (sign(me.x) * sign(a[i].x) > 0) continue;
    Point a(me), b(::a[i]);
    if (a.x > 0) swap(a, b);
    if (a.y == b.y) {
      v.push_back(a.y);
    } else {
      double y = a.y - 1.0 * a.x * (b.y - a.y) / (-a.x + b.x);
      v.push_back(y);
    }
  }
  if ((int)v.size() >= n - k) {
    ok = true; ans = 1e18;
    sort(begin(v), end(v));
    int sz = v.size();
    for (int i = 0; i + n - k - 1 < sz; i++) {
      ans = min(ans, v[i + n - k - 1] - v[i]);
    }
  }

  // x-axis
  v.clear();
  for (int i = 1; i <= n; i++) {
    if (sign(me.y) * sign(a[i].y) > 0) continue;
    Point a(me), b(::a[i]);
    if (a.y > 0) swap(a, b);
    if (a.x == b.x) {
      v.push_back(a.x);
    } else {
      double x = a.x - 1.0 * a.y * (b.x - a.x) / (-a.y + b.y);
      v.push_back(x);
    }
  }
  if ((int)v.size() >= n - k) {
    if (!ok) {
      ok = true; ans = 1e18;
    }
    sort(begin(v), end(v));
    int sz = v.size();
    for (int i = 0; i + n - k - 1 < sz; i++) {
      ans = min(ans, v[i + n - k - 1] - v[i]);
    }
  }


  if (ok) {
    printf("%.6lf\n", ans);
  } else {
    puts("-1");
  }
  return 0;
}