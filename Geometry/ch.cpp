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

  inline int sign(ll x) {
    if (x == 0) return 0;
    else return x < 0 ? -1 : 1;
  }
  inline int dcmp(ll x, ll y) {
    return sign(x - y);
  }

  struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0): x(x), y(y) {}

    void read() { scanf("%lld%lld", &x, &y); }

    Point operator + (const Point& b) const { return Point(x + b.x, y + b.y); }
    Point operator - (const Point& b) const { return Point(x - b.x, y - b.y); }

    bool operator == (const Point& b) const { return x == b.x && y == b.y; }
    bool operator < (const Point& b) const {
      int f = dcmp(x, b.x);
      if (f == -1) return 1;
      else if (f == 1) return 0;
      else return dcmp(y, b.y) == -1;
    }
  };

  ostream& operator<<(ostream& out, const Point& u) {
    return out << "(" << u.x << ", " << u.y << ")";
  }
  istream& operator>>(istream& in, Point& u) {
    return in >> u.x >> u.y;
  }

  ll cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
  ll cross(Point a, Point b, Point c) { return cross(b - a, c - a); }
}
using namespace Geometry;

namespace Polygon {
  // 获得凸包, flag=0 不严格 flag=1 严格 
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
}
using namespace Polygon;

int main() {
  int n, q; vector<Point> v;
  scanf("%d", &n);
  while (n--) {
    Point a; a.read();
    v.push_back(a);
  }
  auto ch = convexHull(v, 0);
  printf("%d\n", ch.size());
  for (auto& x: ch) printf("%lld %lld\n", x.x, x.y);
  return 0;
}