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
const int maxn = 10000 + 5;

const double eps = 1e-14;
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

int n;
double ang[maxn], dis[maxn], dis2[maxn];

double f(double x) {
  while (dcmp(x, pi / 2.0) >= 0) x -= pi / 2;
  while (dcmp(x, 0) < 0) x += pi / 2;
  // while (x >= pi / 2.0) x -= pi / 2;
  // while (x < 0.0) x += pi / 2;
  return x;
}

bool check(double R) {
  int sum = 0, tot = 0;
  vector< pair<double,int> > evs;
  for (int i = 1; i <= n; i++) {
    if (dcmp(dis[i], sqrt(2.0) * R) >= 0) continue;
    if (dcmp(dis[i], R) < 0) return false;
    sum++;
    double v = R / dis[i];
    if (v > 1.0) v = 1.0;
    if (v < -1.0) v = -1.0;
    double ad = acos(v);
    double l = ang[i] - ad;
    double r = ang[i] + ad;
    l = f(l); r = f(r);
    if (dcmp(l, r) < 0) {
      evs.emplace_back(l, 1);
      evs.emplace_back(r + eps, -1);
    } else {
      evs.emplace_back(l, 1);
      evs.emplace_back(pi / 2 + eps, -1);
      evs.emplace_back(0, 1);
      evs.emplace_back(r + eps, -1);
    }
  }
  if (sum == 0) return true;
  sort(begin(evs), end(evs));
  for (auto& ev: evs) {
    tot += ev.second;
    if (tot == sum) return true;
  }
  return false;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int x, y; scanf("%d%d", &x, &y);
    ang[i] = atan2(y, x);
    dis2[i] = 1ll * x * x + 1ll * y * y;
    dis[i] = hypot(x, y);
  }
  double ans = 0, l = 0, r = 1e11;
  for (int i = 0; i < 1000; i++) {
    double m = (l + r) / 2;
    if (check(m)) {
      ans = m;
      l = m;
    } else {
      r = m;
    }
  }
  printf("%.4lf\n", 8.0 * ans);
  return 0;
}