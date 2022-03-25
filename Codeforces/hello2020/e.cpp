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

struct Point {
  int x, y;
  Point(int x = 0, int y = 0): x(x), y(y) {}
};
typedef Point Vector;

ostream& operator<<(ostream& out, const Point& u) {
  return out << "(" << u.x << ", " << u.y << ")";
}

Vector operator + (Vector a, Vector b) { return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (Point a, Point b) { return Vector(a.x - b.x, a.y - b.y); }

ll cross(Vector a, Vector b) { return 1ll * a.x * b.y - 1ll * a.y * b.x; }

int quad(Point p) {
  int x = p.x, y = p.y;
  if (x > 0 && y >= 0) return 1;
  if (x <= 0 && y > 0) return 2;
  if (x < 0 && y <= 0) return 3;
  if (x >= 0 && y < 0) return 4;
  assert(0);
}
bool operator < (const Point& a, const Point& b) {
  int x = quad(a), y = quad(b);
  if (x != y) return x < y;
  return cross(a, b) > 0;
}

int n;
Point a[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int x, y; scanf("%d%d", &x, &y);
    a[i] = Point(x, y);
  }
  ll ans = 0;
  auto c3 = [](int x) {
    return 1ll * x * (x - 1) * (x - 2) / 6;
  };
  for (int i = 1; i <= n; i++) {
    dbg(i);
    vector<Point> vec;
    for (int j = 1; j <= n; j++) {
      if (i == j) continue;
      vec.push_back(a[j] - a[i]);
    }
    sort(begin(vec), end(vec));
    for (int i = 0; i < n - 1; i++) vec.push_back(vec[i]);
    ans += 1ll * (n - 1) * (n - 2) * (n - 3) * (n - 4) / 24;
    for (int i = 0, j = 0; i < n - 1; i++) {
      while (j < i + n - 1 && cross(vec[i], vec[j]) >= 0) {
        j++;
      }
      dbg(i, j);
      ans -= c3(j - i - 1);
    }
  }
  cout << ans << endl;
  return 0;
}