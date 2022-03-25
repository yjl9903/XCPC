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
const int maxn = 3000 + 5;

inline int sign(ll x) {
  if (x == 0) return 0;
  else return x < 0 ? -1 : 1;
}

struct Point {
  int x, y, c;
  Point(int x = 0, int y = 0, int c = -1): x(x), y(y), c(c) {}
  Point operator + (const Point& b) const { return Point(x + b.x, y + b.y); }
  Point operator - (const Point& b) const { return Point(x - b.x, y - b.y); }

  bool operator < (const Point& b) const {
    if (x < b.x) return 1;
    else if (x > b.x) return 0;
    else return y < b.y;
  }
} a[maxn];

ostream& operator<<(ostream& out, const Point& u) {
  return out << "(" << u.x << ", " << u.y << ")";
}

ll dot(Point a, Point b) { return 1ll * a.x * b.x + 1ll * a.y * b.y; }
ll cross(Point a, Point b) { return 1ll * a.x * b.y - 1ll * a.y * b.x; }
ll cross(Point a, Point b, Point c) { return cross(b - a, c - a); }

vector<Point> convexHull(vector<Point> a, bool d) {
  int n = a.size();
  if (n <= 1) return a;
  sort(a.begin(), a.end());
  vector<Point> ans(n * 2);
  int now = -1;
  if (d) {
    for (int i = 0; i < n; i++) {
      while (now > 0 && sign(cross(ans[now - 1], ans[now], a[i])) < 1) now--;
      ans[++now] = a[i];
    }
  } else {
    for (int i = 0; i < n; i++) {
      while (now > 0 && sign(cross(ans[now - 1], ans[now], a[i])) > -1) now--;
      ans[++now] = a[i];
    }
  }
  return ans.resize(now), ans;
}
ll query(const vector<Point>& stk, int x, int y) {
  assert(!stk.empty());
  ll h = stk.front().y, i = stk.front().x;
  ll ans = abs(1ll * x * h - 1ll * y * i);
  for (int l = 0, r = (int)stk.size() - 1, i = 0; l <= r && i <= 5; i++) {
    int len = (r - l) / 3, m1 = l + len, m2 = r - len;
    ll s1 = abs((ll)x * stk[m1].y - (ll)y * stk[m1].x);
    ll s2 = abs((ll)x * stk[m2].y - (ll)y * stk[m2].x);
    if (s1 > s2) {
      r = m2 - 1;
      if (ans < s1) ans = s1;
    } else {
      l = m1 + 1;
      if (ans < s2) ans = s2;
    }
  }
  return ans;
}

int n;

ll solve(vector<Point>& A, vector<Point>& B) {
  ll ans = 0;
  {
    auto vb1 = convexHull(B, true);
    auto vb2 = convexHull(B, false);
    for (auto& x: A) {
      ans = max(ans, query(vb1, x.x, x.y));
      ans = max(ans, query(vb2, x.x, x.y));
    }
  }
  {
    auto va1 = convexHull(A, true);
    auto va2 = convexHull(A, false);
    for (auto& x: B) {
      ans = max(ans, query(va1, x.x, x.y));
      ans = max(ans, query(va2, x.x, x.y));
    }
  }
  return ans;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].c);
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
      vector<Point> v[3];
      for (int j = 1; j <= n; j++) {
        if (a[i].c == a[j].c) continue;
        v[a[j].c].push_back(Point { a[j].x - a[i].x, a[j].y - a[i].y, a[j].c });
      }
      ll cur = 0;
      if (a[i].c == 0) {
        cur = solve(v[1], v[2]);
      } else if (a[i].c == 1) {
        cur = solve(v[0], v[2]);
      } else {
        cur = solve(v[0], v[1]);
      }
      ans = max(ans, cur);
    }
    if (ans % 2 == 0) {
      printf("%lld.0\n", ans / 2);
    } else {
      printf("%lld.5\n", ans / 2);
    }
  }
  return 0;
}