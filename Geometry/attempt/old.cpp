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
};
typedef Point Vector;

ostream& operator<<(ostream& out, const Point& u) {
  return out << "(" << u.x << ", " << u.y << ")";
}

Vector operator + (Vector a, Vector b) { return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (Point a, Point b) { return Vector(a.x - b.x, a.y - b.y); }
Vector operator * (Vector a, double p) { return Vector(a.x * p, a.y * p); }
Vector operator / (Vector a, double p) { return Vector(a.x / p, a.y / p); }
bool operator < (const Point& a, const Point& b) { return a.x < b.x || (a.x == b.x && a.y < b.y); }

bool operator == (const Point& a, const Point& b) {
  return dcmp(a.x, b.x) == 0 && dcmp(a.y, b.y) == 0;
}

double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double length(Vector a) { return sqrt(a.x * a.x + a.y * a.y); }
double distance(Point a, Point b) { return length(b - a); }
double angle(Vector a, Vector b) { return acos(dot(a, b) / length(a) / length(b)); }
double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
double xmult(Point a, Point b, Point c) {
  // 0 -> 三点共线
  // + -> AC 在 AB 的逆时针方向
  // - -> AC 在 AB 的顺时针方向
  return cross(b - a, c - a);
}
double area2(Vector a, Vector b, Vector c) { return cross(b - a, c - a); }

Vector rotate(Vector a, double rad) {
  return Vector(a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad));
}
Vector normal(Vector a) { // 计算单位法线，确保a不是零向量
  double l = length(a); return Vector(-a.y / l, a.x / l);
}
Vector getNormal(Vector a) { return Vector(-a.y, a.x); }

// 直线表示： 已知直线上两个不同点A和B，则方向向量为（B-A），参数方程为 A + (B - A) t
// 直线 t 无限制，射线 t > 0，线段 t 在 0 到 1 之间
struct Line {
  Point p; Vector v;
  Line(Point a, Point b) : p(a), v(b - a) {}
};

Point getLineIntersection(Point p, Vector v, Point q, Vector w) {
  // P + tv 和 Q + wv 有唯一交点，当且仅当 cross(v,w) != 0
  Vector u = p - q;
  double t = cross(w, u) / cross(v, w);
  return p + v * t;
}
double getDistanceToLine(Point p, Point a, Point b) {
  // P 到 AB 的距离
  Vector v1 = b - a, v2 = p - a;
  return fabs(cross(v1, v2)) / length(v1);
}
double getDistanceToSegment(Point p, Point a, Point b) {
  // P 到线段 AB 的距离
  if (a == b) return length(p - a);
  Vector v1 = b - a, v2 = p - a, v3 = p - b;
  if (sign(dot(v1, v2)) < 0) return length(v2);
  else if (sign(dot(v1, v3)) > 0) return length(v3);
  else return fabs(cross(v1, v2)) / length(v1);
}
Point getLineProjection(Point p, Point a, Point b) {
  Vector v = b - a;
  return a + v * (dot(v, p - a) / dot(v, v));
}
bool segmentProperIntersection(Point a1, Point b1, Point a2, Point b2) {
  // 线段重合？
  // 线段相交在端点？
  // 不考虑上述两个case，线段A1B1,A2B2相交 -> 1
  double c1 = cross(b1 - a1, a2 - a1), c2 = cross(b1 - a1, b2 - a1);
  double c3 = cross(b2 - a2, a1 - a2), c4 = cross(b2 - a2, b1 - a2);
  return sign(c1) * sign(c2) < 0 && sign(c3) * sign(c4) < 0;
}
bool onSegment(Point p, Point a1, Point a2) {
  // 点是否在一条线段上（不包含端点）
  return sign(cross(a1 - p, a2 - p)) == 0 && sign(dot(a1 - p, a2 - p)) < 0;
}
// p 是否在直线 a + v * t = 0 上
bool onLine(Point p, Vector v, Point a) {return sign(cross(v, p - a)) == 0;}
// 直线方向向量 v, P点到定点 A 的向量 t, 返回 P 点的参数 t
double getPosOnLine(Vector v, Vector t) {
  if (sign(v.x) == 0) return t.y / v.y;
  return t.x / v.x;
}

// 获取直线与圆的交点，直线 p + v * t = 0, 圆 (x - o.x) ^ 2 + (x - o.y) ^ 2 = r ^ 2
// 返回交点个数和点在直线上的参数 t1 和 t2
int getLineCircleIntersection(Point p, Vector v, Point o, double r, double &t1, double &t2) {
  double a = v.x, b = p.x - o.x, c = v.y, d = p.y - o.y;
  double e = a * a + c * c, f = 2 * (a * b + c * d), g = b * b + d * d - r * r;
  double delta = f * f - 4 * e * g;
  if (sign(delta) < 0)
    return 0;
  if (sign(delta) == 0) {
    t1 = t2 = -f / (2 * e);
    return 1;
  }
  t1 = (-f - sqrt(delta)) / (2 * e);
  t2 = (-f + sqrt(delta)) / (2 * e);
  return 2;
}

double polygonArea(Point* p, int n) {
  // 计算多边形的面积，顶点要按顺序
  double area = 0;
  for (int i = 1; i < n - 1; i++)
    area += cross(p[i] - p[0], p[i + 1] - p[0]);
  return area / 2;
}

int main() {
  Point a(1.0, 2.0);
  return 0;
}