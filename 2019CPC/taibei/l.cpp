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
const ll inf = 1ll << 60;
const int maxn = 4096 + 5;

inline int sign(ll x) {
  if (x == 0) return 0;
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
  bool operator == (const Point& b) const {
    return x == b.x && y == b.y;
  }
} a[maxn];

ostream& operator<<(ostream& out, const Point& u) {
  return out << "(" << u.x << ", " << u.y << ")";
}

ll dot(Point a, Point b) { return 1ll * a.x * b.x + a.y * b.y; }
ll cross(Point a, Point b) { return 1ll * a.x * b.y - a.y * b.x; }
ll cross(Point a, Point b, Point c) { return cross(b - a, c - a); }

vector<Point> convexHull(vector<Point> a) {
  int n = a.size();
  if (n <= 1) return a;
  sort(a.begin(), a.end());
  vector<Point> ans(n * 2);
  int now = -1;
  for (int i = n - 1; i >= 0; i--) {
    while (now > 0 && sign(cross(ans[now - 1], ans[now], a[i])) < 0) now--;
    ans[++now] = a[i];
  }
  return ans.resize(now), ans;
}
vector<Point> convexHull2(vector<Point> a) {
  int n = a.size();
  if (n <= 1) return a;
  sort(a.begin(), a.end());
  vector<Point> ans(n * 2);
  int now = -1;
  for (int i = 0; i < n; i++) {
    while (now > 0 && sign(cross(ans[now - 1], ans[now], a[i])) < 0) now--;
    ans[++now] = a[i];
  }
  return ans.resize(now), ans;
}

ll solve(vector<Point>& a) {
  auto ch1 = convexHull(a);
  auto ch2 = convexHull2(a);
  ll res = 0;
  for (auto& x: a) {
    int id = 0;
    ll ans = cross(x, ch1[0]);
    int l = 0, r = (int)ch1.size() - 1;
    while (l <= r) {
      int len = (r - l) / 3, m1 = l + len, m2 = r - len;
      ll s1 = cross(x, ch1[m1]);
      ll s2 = cross(x, ch1[m2]);
      if (s1 > s2) {
        r = m2 - 1;
        if (ans < s1) ans = s1, id = m1;
      } else {
        l = m1 + 1;
        if (ans < s2) ans = s2, id = m2;
      }
    }
    if (ch1[id] == x) {
      if (id > 0 && cross(x, ch1[id - 1]) == ans) {}
      else if (id + 1 < (int)ch1.size() && cross(x, ch1[id + 1]) == ans) {}
      else continue;
    }


    id = 0;
    ll nx = cross(x, ch2[0]);
    l = 0, r = (int)ch2.size() - 1;
    while (l <= r) {
      int len = (r - l) / 3, m1 = l + len, m2 = r - len;
      ll s1 = cross(x, ch2[m1]);
      ll s2 = cross(x, ch2[m2]);
      if (s1 < s2) {
        r = m2 - 1;
        if (nx > s1) nx = s1, id = m1;
      } else {
        l = m1 + 1;
        if (nx > s2) nx = s2, id = m2;
      }
    }
    if (ch2[id] == x) {
      if (id > 0 && cross(x, ch2[id - 1]) == nx) {}
      else if (id + 1 < (int)ch2.size() && cross(x, ch2[id + 1]) == nx) {}
      else continue;
    }

    res = max(res, ans - nx);
  }
  return res;
}

int n;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", &a[i].x, &a[i].y);
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
      vector<Point> v;
      for (int j = 1; j <= n; j++) {
        if (i == j) continue;
        v.push_back(a[j] - a[i]);
      }
      ans = max(ans, solve(v));
    }
    if (ans % 2 == 0) {
      printf("%lld\n", ans / 2);
    } else {
      printf("%lld.5\n", ans / 2);
    }
  }
  return 0;
}