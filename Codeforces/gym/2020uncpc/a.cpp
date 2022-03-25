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
const int maxn = 200000 + 5;

namespace Geometry {
  const long double eps = 1e-14;
  const long double pi = acos(-1.0);

  inline int sign(long double x) {
    if (fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
  }
  inline int dcmp(long double x, long double y) {
    return sign(x - y);
  }
  inline int zero(long double x) {
    return fabs(x) < eps;
  }

  struct Point {
    long double x, y;
    Point(long double x = 0, long double y = 0): x(x), y(y) {}

    void read() {
      int a, b;
      scanf("%d%d", &a, &b);
      x = a;
      y = b;
    }

    Point operator + (const Point& b) const { return Point(x + b.x, y + b.y); }
    Point operator - (const Point& b) const { return Point(x - b.x, y - b.y); }
    Point operator * (long double p) { return Point(x * p, y * p); }
    Point operator / (long double p) { return Point(x / p, y / p); }

    bool operator == (const Point& b) const { return dcmp(x, b.x) == 0 && dcmp(y, b.y) == 0; }
    bool operator < (const Point& b) const {
      int f = dcmp(x, b.x);
      if (f == -1) return 1;
      else if (f == 1) return 0;
      else return dcmp(y, b.y) == -1;
    }

    long double abs() { return sqrt(x * x + y * y); }
    long double abs2() { return x * x + y * y; }
    long double distance(const Point& b) { return (*this - b).abs(); }

    Point unit() { return *this / abs(); }
  };

  ostream& operator<<(ostream& out, const Point& u) {
    return out << "(" << u.x << ", " << u.y << ")";
  }
  istream& operator>>(istream& in, Point& u) {
    return in >> u.x >> u.y;
  }
}
using namespace Geometry;

Point a, b, c, d;

inline long double sqr(long double x) {
  return x * x;
}

long double cal(long double L, long double R, function<long double(long double)> eval) {
  long double ans = min(eval(L), eval(R));
  long double l = L, r = R;
  for (int i = 0; i < 20000; i++) {
    long double ml = l + (r - l) / 3.0;
    long double mr = r - (r - l) / 3.0;
    ans = min(ans, eval(ml));
    ans = min(ans, eval(mr));
    if (eval(ml) > eval(mr)) {
      l = ml;
    } else {
      r = mr;
    }
  }
  if (sign(ans) <= 0) {
    return 0.0;
  }
  return ans;
}

int main() {
  a.read();
  b.read();
  c.read();
  d.read();
  
  Point k1, k2;
  if (a == b) k1.x = k1.y = 0;
  else k1 = (b - a).unit();
  if (c == d) k2.x = k2.y = 0;
  else k2 = (d - c).unit();

  long double ab = a.distance(b), cd = c.distance(d);

  long double ans = cal(0, min(ab, cd), [&](long double t) {
    long double dx = (a.x + k1.x * t) - (c.x + k2.x * t);
    long double dy = (a.y + k1.y * t) - (c.y + k2.y * t);
    return dx * dx + dy * dy;
  });

  if (dcmp(ab, cd) < 0) {
    ans = min(ans, cal(ab, cd, [&](long double t) {
      long double dx = b.x - (c.x + k2.x * t);
      long double dy = b.y - (c.y + k2.y * t);
      return dx * dx + dy * dy;
    }));
  } else if (dcmp(ab, cd) > 0) {
    ans = min(ans, cal(cd, ab, [&](long double t) {
      long double dx = (a.x + k1.x * t) - d.x;
      long double dy = (a.y + k1.y * t) - d.y;
      return dx * dx + dy * dy;
    }));
  }

  printf("%.10Lf\n", sqrt(ans));

  return 0;
}