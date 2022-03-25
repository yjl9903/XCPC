#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int, int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;
const double pi = acos(-1.0);

namespace {
double pow2(double x) { return x * x; }

double pow3(double x) { return x * x * x; }

double dis(double x1, double y1, double z1, double x2, double y2, double z2) {
  return pow2(x1 - x2) + pow2(y1 - y2) + pow2(z1 - z2);
}

double cos(double a, double b, double c) { return (b * b + c * c - a * a) / (2 * b * c); }

double cap(double r, double h) { return pi * (r * 3 - h) * h * h / 3; }

// 2球体积交
double sphere_intersect(double x1, double y1, double z1, double r1, double x2, double y2, double z2, double r2) {
  double d = dis(x1, y1, z1, x2, y2, z2);
  //相离
  if (d >= pow2(r1 + r2)) return 0;
  //包含
  if (d <= pow2(r1 - r2)) return pow3(min(r1, r2)) * 4 * pi / 3;
  //相交
  double h1 = r1 - r1 * cos(r2, r1, sqrt(d)), h2 = r2 - r2 * cos(r1, r2, sqrt(d));
  return cap(r1, h1) + cap(r2, h2);
}
}  // namespace

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    int x1, y1, z1;
    int x2, y2, z2;
    int x3, y3, z3;
    int x4, y4, z4;
    scanf("%d%d%d", &x1, &y1, &z1);
    scanf("%d%d%d", &x2, &y2, &z2);
    scanf("%d%d%d", &x3, &y3, &z3);
    scanf("%d%d%d", &x4, &y4, &z4);
    int k1, k2;
    scanf("%d%d", &k1, &k2);

    double r1 = 0;
    double rx1 = (1.0 * k1 * k1 * x2 - x1) / (1.0 * k1 * k1 - 1);
    double ry1 = (1.0 * k1 * k1 * y2 - y1) / (1.0 * k1 * k1 - 1);
    double rz1 = (1.0 * k1 * k1 * z2 - z1) / (1.0 * k1 * k1 - 1);
    r1 += pow2(1.0 * k1 * (x2 - x1) / (1.0 * k1 * k1 - 1));
    r1 += pow2(1.0 * k1 * (y2 - y1) / (1.0 * k1 * k1 - 1));
    r1 += pow2(1.0 * k1 * (z2 - z1) / (1.0 * k1 * k1 - 1));

    double r2 = 0;
    double rx2 = (1.0 * k2 * k2 * x4 - x3) / (1.0 * k2 * k2 - 1);
    double ry2 = (1.0 * k2 * k2 * y4 - y3) / (1.0 * k2 * k2 - 1);
    double rz2 = (1.0 * k2 * k2 * z4 - z3) / (1.0 * k2 * k2 - 1);
    r2 += pow2(1.0 * k2 * (x4 - x3) / (1.0 * k2 * k2 - 1));
    r2 += pow2(1.0 * k2 * (y4 - y3) / (1.0 * k2 * k2 - 1));
    r2 += pow2(1.0 * k2 * (z4 - z3) / (1.0 * k2 * k2 - 1));

    double ans = sphere_intersect(rx1, ry1, rz1, sqrt(r1), rx2, ry2, rz2, sqrt(r2));
    printf("%.3lf\n", ans);
  }
}