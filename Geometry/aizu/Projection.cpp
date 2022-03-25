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

const double eps = 1e-5;
const double pi = acos(-1.0);

inline int sign(double x) {
  // double大小比较，考虑精度 eps
  if (fabs(x) < eps) return 0;
  else return x < 0 ? -1 : 1;
}
inline int dcmp(double x, double y) {
  return sign(x - y);
}
inline int zero(double x) {
  return fabs(x) < eps;
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

bool operator < (const Point& a, const Point& b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator == (const Point& a, const Point& b) {
  return dcmp(a.x, b.x) == 0 && dcmp(a.y, b.y) == 0;
}

double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
double angle(Point a, Point b) { return acos(dot(a, b) / a.abs() / b.abs()); }
double cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
double xmult(Point a, Point b, Point c) {
  // 0 -> 三点共线
  // + -> AC 在 AB 的逆时针方向
  // - -> AC 在 AB 的顺时针方向
  return cross(b - a, c - a);
}
double area2(Point a, Point b, Point c) { return cross(b - a, c - a); }

Point normal(Point a) { // 计算单位法线，确保a不是零向量
  double l = a.abs(); return Point(-a.y / l, a.x / l);
}

// a -> b
struct Line {
  Point p[2];
  Line() {}
  Line(Point a, Point b) { p[0] = a; p[1] = b; }
  void read() { p[0].read(); p[1].read(); }
  Point& operator [](int i) { return p[i]; }

  Point projection(const Point& q) {
    Point k = p[1] - p[0];
    return p[0] + k * (dot(q - p[0], k) / k.abs2());
  }
};

int main() {
  Line l; l.read();
  int q; scanf("%d", &q);
  while (q--) {
    Point q; q.read();
    Point p = l.projection(q);
    printf("%.8lf %.8lf\n", p.x, p.y);
  }
  return 0;
}
