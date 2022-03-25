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

using db = long double;

namespace Geometry {

  const db eps = (db)1e-20;
  const db pi = acos(-1.0);

  inline int sign(db x) {
    if (fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
  }
  inline int dcmp(db x, db y) {
    return sign(x - y);
  }
  inline int zero(db x) {
    return fabs(x) < eps;
  }

  // x 在 [l, r] 内或 [r, l] 内
  inline int inMid(db l, db r, db x) {
    return dcmp(l, x) * dcmp(r, x) <= 0;
  }

  struct Point {
    db x, y; int id, turn;
    Point(db x = 0, db y = 0): x(x), y(y) {}

    void read() { scanf("%lf%lf", &x, &y); }

    Point operator + (const Point& b) const { return Point(x + b.x, y + b.y); }
    Point operator - (const Point& b) const { return Point(x - b.x, y - b.y); }
    Point operator * (db p) { return Point(x * p, y * p); }
    Point operator / (db p) { return Point(x / p, y / p); }

    bool operator == (const Point& b) const { return dcmp(x, b.x) == 0 && dcmp(y, b.y) == 0; }
    bool operator < (const Point& b) const {
      int f = dcmp(x, b.x);
      if (f == -1) return 1;
      else if (f == 1) return 0;
      else return dcmp(y, b.y) == -1;
    }

    db abs() { return sqrt(x * x + y * y); }
    db abs2() { return x * x + y * y; }
    db distance(const Point& b) { return (*this - b).abs(); }

    // 逆时针旋转
    Point rot90(){ return Point(-y, x); }
    Point rot(db r) {
      return Point(x * cos(r) - y * sin(r), x * sin(r) + y * cos(r));
    }
    Point unit() { return *this / abs(); }

    Point getdel() {
      if (sign(x) == -1 || (sign(x) == 0 && sign(y) == -1))
        return (*this) * (-1);
      else
        return (*this);
    }
  };

  ostream& operator<<(ostream& out, const Point& u) {
    return out << "(" << u.x << ", " << u.y << ")";
  }
  istream& operator>>(istream& in, Point& u) {
    return in >> u.x >> u.y;
  }

  db dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
  db angle(Point a, Point b) { return acos(dot(a, b) / a.abs() / b.abs()); }
  db cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
  db cross(Point a, Point b, Point c) { return cross(b - a, c - a); }

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
}
using namespace Geometry;

namespace CircleGeometry {
  struct Circle {
    Point o; db r;
  };

  // 返回两个圆的公切线数量
  int checkposCC(Circle k1, Circle k2) {
    if (dcmp(k1.r,k2.r) == -1) swap(k1, k2);
    db dis = k1.o.distance(k2.o);
    int w1 = dcmp(dis, k1.r + k2.r);
    int w2 = dcmp(dis, k1.r - k2.r);
    if (w1 > 0) return 4;
    else if (w1 == 0) return 3;
    else if (w2 > 0) return 2; 
    else if (w2 == 0) return 1;
    else return 0;
  }

  // 沿圆 k1 逆时针给出 , 相切给出两个 
  vector<Point> getCC(Circle k1, Circle k2) {
    int pd = checkposCC(k1, k2);
    if (pd == 0 || pd == 4) return {};
    db a = (k2.o - k1.o).abs2();
    db cosA = (k1.r * k1.r + a - k2.r * k2.r) / (2 * k1.r * sqrt(max(a, (db)0.0)));
    db b = k1.r * cosA;
    db c = sqrt(max((db)0.0, k1.r * k1.r - b * b));
    Point k = (k2.o - k1.o).unit();
    Point m = k1.o + k * b;
    Point del = k.rot90() * c;
    return vector<Point> { m - del, m + del };
  } 

  // 沿圆 k1 逆时针给出 
  vector<Point> tangentCP(Circle k1, Point k2) {
    db a = (k2 - k1.o).abs();
    db b = k1.r * k1.r/a;
    db c = sqrt(max((db)0.0, k1.r * k1.r - b * b));
    Point k = (k2 - k1.o).unit();
    Point m = k1.o + k * b;
    Point del = k.rot90() * c;
    return vector<Point> { m - del, m + del };
  }

  vector<Line> tangentOutCC(Circle k1, Circle k2) {
    int pd = checkposCC(k1, k2);
    if (pd == 0) {
      return {};
    } else if (pd == 1) {
      Point k = getCC(k1,k2)[0];
      return { Line { k, k } };
    }
    if (dcmp(k1.r, k2.r) == 0) {
      Point del = (k2.o - k1.o).unit().rot90().getdel();
      return {
        Line { k1.o - del * k1.r, k2.o - del * k2.r },
        Line { k1.o + del * k1.r, k2.o + del * k2.r } 
      };
    } else {
      Point p = (k2.o * k1.r - k1.o * k2.r) / (k1.r - k2.r);
      vector<Point> A = tangentCP(k1, p), B = tangentCP(k2, p);
      vector<Line> ans;
      for (int i = 0; i < A.size(); i++)
        ans.push_back({ A[i], B[i] }); 
      return ans;
    }
  }
}
using namespace CircleGeometry;

vector<Point> convexHull(vector<Point> a, int flag = 1) {
  int n = a.size();
  if (n <= 1) return a;
  sort(a.begin(), a.end());
  vector<Point> ans(n * 2);
  int now = -1;
  for (int i = 0; i < n; i++) {
    while (now > 0 && sign(cross(ans[now - 1], ans[now], a[i])) < flag) now--;
    ans[++now] = a[i];
  }
  int pre = now;
  for (int i = n - 2; i >= 0; i--) {
    while (now > pre && sign(cross(ans[now - 1], ans[now], a[i])) < flag) now--;
    ans[++now] = a[i];
  }
  return ans.resize(now), ans;
}

int n, rr[1005];
Point a[1005];

int main() {
  scanf("%d", &n);
  vector<Point> vec;
  for (int i = 1, x, y, r; i <= n; i++) {
    scanf("%d%d%d", &x, &y, &r);
    rr[i] = r; a[i] = Point(x, y); a[i].id = i;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      auto res = tangentOutCC({ a[i], 1.0 * rr[i] }, { a[j], 1.0 * rr[j] });
      for (const Line& li: res) {
        auto a = li.p[0], b = li.p[1];
        a.id = i; b.id = j;
        vec.push_back(a); vec.push_back(b);
      }
    }
  }
  auto res = convexHull(vec, 0);
  db ans = 0;
  auto check = [&](const Point& a, const Point& b) {
    if (a.id != b.id) return ;
    Point o = ::a[a.id];
    db ang = angle(a - o, b - o);
    ans = max((db)ans, ang * rr[a.id]);
  };
  for (int i = 0; i + 1 < (int)res.size(); i++) {
    // cout << res[i].x << ' ' << res[i].y << endl;
    check(res[i], res[i + 1]);
  }
  // cout << res.back().x << ' ' << res.back().y << endl;
  check(res.back(), res.front());
  printf("%.8Lf\n", ans);
  return 0;
}