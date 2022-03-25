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

namespace Geometry {
  const long double eps = 1e-16;
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

  // x 在 [l, r] 内或 [r, l] 内
  inline int inMid(long double l, long double r, long double x) {
    return dcmp(l, x) * dcmp(r, x) <= 0;
  }

  struct Point {
    long double x, y;
    Point(long double x = 0, long double y = 0): x(x), y(y) {}

    void read() { scanf("%lf%lf", &x, &y); }

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

    long double abs() const { return sqrt(x * x + y * y); }
    long double abs2() const { return x * x + y * y; }
    long double distance(const Point& b) const { return (*this - b).abs(); }

    // 逆时针旋转
    Point rot90(){ return Point(-y, x); }
    Point rot(long double r) {
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

  long double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
  long double angle(Point a, Point b) { return acos(dot(a, b) / a.abs() / b.abs()); }
  long double cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
  long double cross(Point a, Point b, Point c) { return cross(b - a, c - a); }

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

    long double length() const {
      return p[0].distance(p[1]);
    }

    // q 在直线上的投影点
    Point projection(const Point& q) {
      Point k = p[1] - p[0];
      return p[0] + k * (dot(q - p[0], k) / k.abs2());
    }
    // q 在直线上的对称点
    Point reflection(const Point& q) {
      return projection(q) * 2 - q;
    }

    long double distance(const Point& q) {
      Point k = projection(q);
      return q.distance(k);
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
  bool intersect(long double l1, long double r1, long double l2, long double r2) {
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
    long double a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
	  return (p1 * a2 + p2 * a1) / (a1 + a2);
  }
  // 获取直线 L1 和 L2 的交点
  Point getLineIntersection(Line l1, Line l2) {
    return getLineIntersection(l1[0], l1[1], l2[0], l2[1]);
  }
}
using namespace Geometry;

namespace Polygon {
  // 多边形的面积
  long double area(const vector<Point>& a) {
    long double ans = 0;
    for (int i = 0, sz = a.size(); i < sz; i++) {
      ans += cross(a[i], a[(i + 1) % sz]);
    }
    return abs(ans / 2.0);
  }
  // 多边形以逆时针顺序给出
  // 判断一个多边形是否为凸多边形
  bool isConvex(vector<Point> a) {
    int n = a.size(); a.push_back(a[0]); a.push_back(a[1]);
    for (int i = 0; i < n; i++) {
      if (clockwise(a[i], a[i + 1], a[i + 2]) == -1) {
        return false;
      }
    }
    return true;
  }
  // 多边形以逆时针顺序给出
  // 判断点和多边形的关系, 2 内部, 1 边界, 0 外部
  int contain(vector<Point> a, const Point& q) {
    int pd = 0; a.push_back(a[0]);
    for (int i = 1; i < (int)a.size(); i++) {
      Point u = a[i - 1], v = a[i];
      if (onSegment(u, v, q)) return 1;
      if (dcmp(u.y, v.y) > 0) swap(u, v);
      if (dcmp(u.y, q.y) >= 0 || dcmp(v.y, q.y) < 0) continue;
      if (sign(cross(u - v, q - v)) < 0) pd ^= 1;
    }
    return pd * 2;
  }
}
using namespace Polygon;

int n, R, A, B;

bool checkCP(const vector<Point>& poly, const Point& x) {
  if (contain(poly, x) == 2) {
    for (int i = 0; i < (int)poly.size(); i++) {
      int j = i + 1 < (int)poly.size() ? i + 1 : 0;
      Line tot(poly[i], poly[j]);
      if (dcmp(tot.distance(x), R) < 0) {
        return false;
      }
    }
    return true;
  } else {
    return false;
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &n, &R, &A, &B);
    vector<Point> vec;
    for (int i = 0; i < n; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      vec.push_back(Point(x, y));
    }
    if (A <= B) {
      long double ans = area(vec) * A;
      printf("%.8lf\n", ans);
    } else {
      long double a1 = area(vec), a2 = 0;
      for (int i = 0; i < (int)vec.size(); i++) {
        int j = i + 1 < (int)vec.size() ? i + 1 : 0;
        int k = i - 1 > -1 ? i - 1 : (int)vec.size() - 1;

        Line l1(vec[i], vec[j]);
        Line l2(vec[i], vec[k]);
        // if (l1.length() > l2.length()) {
        //   swap(l1, l2);
        // }
        // Point d = (l2[1] - l2[0]) * (l1.length() / l2.length());
        // Point tag = (l1[1] + vec[i] + d) / 2.0;
        Point tag = (l1[0] + (l1[1] - l1[0]).unit() + l2[0] + (l2[1] - l2[0]).unit()) / 2.0;

        long double alpha = angle(l1.dir(), tag - vec[i]);
        assert(dcmp(0, alpha) <= 0 && dcmp(alpha, pi / 2) <= 0);
        long double L = R / sin(alpha);

        Point o = vec[i] + (tag - vec[i]).unit() * L;

        if (checkCP(vec, o)) {
          long double sa = 1.0 * R * R / tan(alpha);
          long double oalpha = pi - alpha - alpha;
          long double sb = 1.0 * R * R / 2.0 * oalpha;

          a2 += sa - sb;
        }
      }
      double ans = a2 * A + (a1 - a2) * B;
      printf("%.8lf\n", ans);
    }
  }
  return 0;
}