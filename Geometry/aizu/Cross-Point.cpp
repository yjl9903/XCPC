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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

namespace Geometry {
  const double eps = 1e-5;
  const double pi = acos(-1.0);

  inline int sign(double x) {
    if (fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
  }
  inline int dcmp(double x, double y) {
    return sign(x - y);
  }
  inline int zero(double x) {
    return fabs(x) < eps;
  }

  // x 在 [l, r] 内或 [r, l] 内
  inline int inMid(double l, double r, double x) {
    return dcmp(l, x) * dcmp(r, x) <= 0;
  }

  struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}

    void read() { scanf("%lf%lf", &x, &y); }

    Point operator + (const Point& b) const { return Point(x + b.x, y + b.y); }
    Point operator - (const Point& b) const { return Point(x - b.x, y - b.y); }
    Point operator * (double p) { return Point(x * p, y * p); }
    Point operator / (double p) { return Point(x / p, y / p); }

    double abs() { return sqrt(x * x + y * y); }
    double abs2() { return x * x + y * y; }
    double distance(const Point& b) { return (*this - b).abs(); }

    // 逆时针旋转
    Point rot90(){ return Point(-y, x); }
    Point rot(double r) {
      return Point(x * cos(r) - y * sin(r), x * sin(r) + y * cos(r));
    }
    Point unit() { return *this / abs(); }
  };

  ostream& operator<<(ostream& out, const Point& u) {
    return out << "(" << u.x << ", " << u.y << ")";
  }
  istream& operator>>(istream& in, Point& u) {
    return in >> u.x >> u.y;
  }

  bool operator < (const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
  }

  bool operator == (const Point& a, const Point& b) {
    return dcmp(a.x, b.x) == 0 && dcmp(a.y, b.y) == 0;
  }

  double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
  double angle(Point a, Point b) { return acos(dot(a, b) / a.abs() / b.abs()); }
  double cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
  double cross(Point a, Point b, Point c) { return cross(b - a, c - a); }

  // C 在 B 的逆时针方向 1, 顺时针方向 -1, 共线 0
  int clockwise(Point a, Point b, Point c) { return sign(cross(b - a, c - a)); }

  // p[0] -> p[1]
  struct Line {
    Point p[2];
    Line() {}
    Line(Point a, Point b) { p[0] = a; p[1] = b; }

    void read() { p[0].read(); p[1].read(); }
    Point& operator [](int i) { return p[i]; }
    Point dir() { return p[1] - p[0]; }

    // q 在直线上的投影点
    Point projection(const Point& q) {
      Point k = p[1] - p[0];
      return p[0] + k * (dot(q - p[0], k) / k.abs2());
    }
    // q 在直线上的对称点
    Point reflection(const Point& q) {
      return projection(q) * 2 - q;
    }
  };

  // q 是否在线段 L 上
  bool onSegment(Line l, const Point& q) {
    return sign(cross(q - l[0], l[1] - l[0])) == 0 && 
      inMid(l[0].x, l[1].x, q.x) && inMid(l[0].y, l[1].y, q.y);
  }
  // q 是否在线段 AB 上
  bool onSegment(Point a, Point b, Point q) {
    return onSegment(Line(a, b), q);
  }
  // 直线 L1 和 L2 是否平行
  bool isParallel(Line l1, Line l2) {
    return sign(cross(l1.dir(), l2.dir())) == 0;
  }
  // 射线 L1 和 L2 的方向是否相同
  bool isSameDir(Line l1, Line l2) {
    return isParallel(l1, l2) && sign(dot(l1.dir(), l2.dir())) == 1;
  }
  // 直线 L1 和 L2 是否正交
  bool isOrthogonal(Line l1, Line l2) {
    return sign(dot(l1.dir(), l2.dir())) == 0;
  }

  // 区间 [l1, r1] 和 [l2, r2] 是否相交
  bool intersect(double l1, double r1, double l2, double r2) {
    if (l1 > r1) swap(l1, r1);
    if (l2 > r2) swap(l2, r2); 
    return !(dcmp(r1, l2) == -1 || dcmp(r2 ,l1) == -1);
  }
  // 线段 P1P2 和 Q1Q2 是否相交
  bool isSegmentIntersect(Point p1, Point p2, Point q1, Point q2) {
    return intersect(p1.x, p2.x, q1.x, q2.x) && 
      intersect(p1.y, p2.y, q1.y, q2.y) && 
      sign(cross(p1, p2, q1)) * sign(cross(p1, p2, q2)) <= 0 && 
      sign(cross(q1, q2, p1)) * sign(cross(q1, q2, p2)) <= 0;
  }
  // 线段 L1 和 L2 是否相交
  bool isSegmentIntersect(Line l1, Line l2) {
    return isSegmentIntersect(l1[0], l1[1], l2[0], l2[1]);
  }
  // 获取直线 P1P2 和 Q1Q2 的交点
  Point getLineIntersection(Point p1, Point p2, Point q1, Point q2) {
    double a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	  return (p1 * a2 + p2 * a1) / (a1 + a2);
  }
  // 获取直线 L1 和 L2 的交点
  Point getLineIntersection(Line l1, Line l2) {
    return getLineIntersection(l1[0], l1[1], l2[0], l2[1]);
  }
}
using namespace Geometry;

int main() {
  int q; scanf("%d", &q);
  while (q--) {
    Line l1, l2;
    l1.read(); l2.read();
    auto x = getLineIntersection(l1, l2);
    printf("%.8lf %.8lf\n", x.x, x.y);
  }
  return 0;
}