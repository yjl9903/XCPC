#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef long double lld;
const int maxn = 1000 + 5;
const double eps = 1e-8;
const double pi = acos(-1.0);

lld x1, y1, r1, x2, y2, r2;

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
};

struct Circle {
  Point o; long double r;
};

ll getCirclesIntersectionArea(const Circle& a, const Circle& b) { 

}

lld dis(Point a, Point b){ a.x -= b.x; a.y -= b.y; return sqrt(a.x * a.x + a.y * a.y); }

int main(){
  cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
  Point a(x1, y1), b(x2, y2);
  lld d = dis(a, b), minr = min(1.0 * r1, 1.0 * r2);
  if (dcmp(d - 1.0 * r1 - 1.0 * r2) >= 0) return printf("%.10lf", 0.0), 0; 
  if (dcmp(d - fabs(1.0 * r1 - 1.0 * r2)) <= 0) return printf("%.10lf", double(pi * minr * minr)), 0;

  lld a1 = 2*acos((1.0*r1*r1+d*d-1.0*r2*r2)/(2.0*r1*d));
  lld a2 = 2*acos((1.0*r2*r2+d*d-1.0*r1*r1)/(2.0*r2*d));
  lld ans = 1.0*r1*r1*a1/2.0 + 1.0*r2*r2*a2/2.0 - 1.0*r1*r1*sin(a1)/2.0 - 1.0*r2*r2*sin(a2)/2.0;
  printf("%.10lf", (double)ans);
  return 0;
}