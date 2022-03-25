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
#include <random>
#include <ctime>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;
const double eps = 1e-6;
const double pi = acos(-1.0);

inline int dcmp(double x) {
  if (fabs(x) < eps) return 0;
  else return x < 0 ? -1 : 1;
}
inline int dcmp(double x, double y) {
  return dcmp(x - y);
}

struct Point {
  double x, y;
  Point(double x = 0, double y = 0): x(x), y(y) {}
};

Point operator + (Point a, Point b) { return Point(a.x + b.x, a.y + b.y); }
Point operator - (Point a, Point b) { return Point(a.x - b.x, a.y - b.y); }

double length(Point a) { return sqrt(a.x * a.x + a.y * a.y); }
double distance(Point a, Point b) { return length(b - a); }

double minCircle(vector<Point> p) {
  shuffle(begin(p), end(p), mt19937(time(0)));
  auto sqr = [](double x) { return x * x; };
  auto getO = [&sqr](Point p1, Point p2, Point p3) {
    double a = p2.x - p1.x;
    double b = p2.y - p1.y;
    double c = p3.x - p2.x;
    double d = p3.y - p2.y;
    double e = sqr(p2.x) + sqr(p2.y) - sqr(p1.x) - sqr(p1.y);
    double f = sqr(p3.x) + sqr(p3.y) - sqr(p2.x) - sqr(p2.y);
    Point res;
    res.x = (f * b - e * d) / (c * b - a * d) / 2.0; 
    res.y = (a * f - e * c) / (a * d - b * c) / 2.0;
    return res;
  };
  Point O = p[1]; 
  double R = 0;
  int n = (int)p.size();
  for (int i = 0; i < n; i++) {
    if (dcmp(distance(p[i], O), R) <= 0) continue;
    O = p[i]; R = 0;
    for (int j = 0; j < i; j++) {
      if (dcmp(distance(p[j], O), R) <= 0) continue;
      O = (Point){ (p[i].x + p[j].x) / 2.0, (p[i].y + p[j].y) / 2.0 };
      R = distance(p[i], p[j]) / 2.0;
      for (int k = 0; k < j; k++) {
        if (dcmp(distance(p[k], O), R) <= 0) continue;
        O = getO(p[i], p[j], p[k]);
        R = distance(p[i], O);
      }
    }
  }
  return R;
} 

const int N = 10000;

int main() {
  int n; scanf("%d", &n);
  vector<Point> v;
  for (int i = 1; i <= n; i++) {
    int x, y, r; scanf("%d%d%d", &x, &y, &r);
    for (int j = 0; j < N; j++) {
      double t = j * 2.0 * pi / N;
      double xx = x + r * cos(t);
      double yy = y + r * sin(t);
      v.push_back((Point){xx, yy});
    }
  }
  printf("%.4lf\n", minCircle(v));
  return 0;
}