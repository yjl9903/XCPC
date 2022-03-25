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
const int maxn = 100000 + 5;

int n;

inline int sign(ll x) {
  if (fabs(x) <= 0) return 0;
  else return x < 0 ? -1 : 1;
}
inline int dcmp(ll x, ll y) {
  return sign(x - y);
}

struct Point {
  int x, y;
  Point(int x = 0, int y = 0): x(x), y(y) {}
  Point operator + (const Point& b) const { return Point(x + b.x, y + b.y); }
  Point operator - (const Point& b) const { return Point(x - b.x, y - b.y); }
  bool operator < (const Point& b) const {
    int f = dcmp(x, b.x);
    if (f == -1) return 1;
    else if (f == 1) return 0;
    else return dcmp(y, b.y) == -1;
  }
} a[maxn];

ostream& operator<<(ostream& out, const Point& u) {
  return out << "(" << u.x << ", " << u.y << ")";
}

ll cross(Point a, Point b) { return 1ll * a.x * b.y - 1ll * a.y * b.x; }
ll cross(Point a, Point b, Point c) { return cross(b - a, c - a); }

ll area(const vector<Point>& a) {
  ll ans = 0;
  for (int i = 0, sz = a.size(); i < sz; i++) {
    ans += cross(a[i], a[(i + 1) % sz]);
  }
  return abs(ans);
}

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

int main() {
  scanf("%d", &n);
  vector<Point> v;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].x, &a[i].y);
  }
  if (n % 2) return puts("NO"), 0;
  Point m = a[1] + a[1 + n / 2];
  for (int i = 1; i <= n / 2; i++) {
    Point x = a[i] + a[i + n / 2];
    if (x.x != m.x || x.y != m.y) {
      puts("NO"); return 0;
    }
  }
  puts("YES");
  return 0;
}