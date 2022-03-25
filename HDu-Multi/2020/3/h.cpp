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
const int maxn = 200000 + 5;

namespace Geometry {
  const double eps = 1e-9;
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

    bool operator == (const Point& b) const { return dcmp(x, b.x) == 0 && dcmp(y, b.y) == 0; }
    bool operator < (const Point& b) const {
      int f = dcmp(x, b.x);
      if (f == -1) return 1;
      else if (f == 1) return 0;
      else return dcmp(y, b.y) == -1;
    }

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

    double distance(const Point& q) {
      Point k = projection(q);
      return k.distance(q);
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

  // 获取点 Q 到线段 L 的距离
  double disPointSegment(Point q, Line l) {
    Point k = l.projection(q);
    if (onSegment(l, k)) {
      return q.distance(k);
    } else {
      return min(q.distance(l[0]), q.distance(l[1]));
    }
  }
  // 获取线段 L1 和 L2 的距离
  double disSegment(Line l1, Line l2) {
    if (isSegmentIntersect(l1, l2)) return 0.0;
    return min(min(disPointSegment(l2[0], l1), disPointSegment(l2[1], l1)),
      min(disPointSegment(l1[0], l2), disPointSegment(l1[1], l2)));
  }
}
using namespace Geometry;

int L, x, y, vx, vy, k;
double H;

Point A, B, C;
Line l1, l2;

ll cal(double t) {
  ll ans = 0;
  Point ed = Point(x, y) + Point(vx, vy) * t;
  {
    ll tot = 0;
    if (sign(ed.y) > 0) {
      tot += ll(abs(ed.y) / H);
    } else if (sign(ed.y) < 0) {
      tot += ll(abs(ed.y) / H) + 1;
    }
    ans += tot;
    // dbg(ed.y, tot);
  }
  {
    double dis = l1.distance(ed);
    int dir = clockwise(A, B, ed);
    ll tot = 0;
    if (dir == -1) {
      tot += ll(dis / H);
    } else if (dir == 1) {
      tot += ll(dis / H) + 1;
    }
    ans += tot;
    // dbg(dis, tot);
  }
  {
    double dis = l2.distance(ed);
    int dir = clockwise(A, C, ed);
    ll tot = 0;
    if (dir == 1) {
      tot += ll(dis / H);
    } else if (dir == -1) {
      tot += ll(dis / H) + 1;
    }
    ans += tot;
    // dbg(dis, tot);
  }
  return ans;
}

const int Turn = 5000;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d%d%d", &L, &x, &y, &vx, &vy, &k);
    H = sqrt(3.0) * L / 2.0;

    A = Point(0, H);
    B = Point(L / 2.0, 0);
    C = Point(-L / 2.0, 0);
    l1 = Line(A, B);
    l2 = Line(A, C);

    // ll cnt = cal(1.00002957);
    // dbg(cnt);
    double l = 0.0, r = 1.0 * L * k;
    for (int i = 0; i < Turn; i++) {
      double m = (l + r) / 2.0;
      if (cal(m) < k) {
        l = m;
      } else {
        r = m;
      }
      // dbg(cal(m), l, r);
    }
    dbg(l, r);
    printf("%.6lf\n", l);
  }
  return 0;
}