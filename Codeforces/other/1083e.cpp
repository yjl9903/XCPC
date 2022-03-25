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
const int maxn = 1000000 + 5;

struct LineContainer  {
  static const ll inf = 2e18;
  static bool modeQ; // Toggles operator < mode
 
  struct Line {
    mutable ll a, b, end;
    ll intersect(const Line& r) const {
      if (a == r.a) return b > r.b ? inf : -inf;
      ll u = b - r.b, d = r.a - a;
      return u / d - ((u ^ d) < 0 && u % d);
    }
    bool operator<(const Line& r) const {
      return modeQ ? end < r.end : a < r.a;
    }
  };
 
  multiset<Line> S;
  void clear() { S.clear(); }

  // Updates segment end
  bool update(multiset<Line>::iterator it) {
    auto cur = it++; cur->end = inf;
    if (it == S.end()) return false;
    cur->end = cur->intersect(*it);
    return cur->end >= it->end;
  }

  // Insert f(x) = ax + b, time: O(log n)
  void insert(ll a, ll b) {
    auto it = S.insert({ a, b, inf });
    while (update(it)) it = --S.erase(++it);
    while (it != S.begin() && update(--it)) {
      update(it = --S.erase(++it));
    }
    while (it != S.begin() && update(--it)) {
      update(it = --S.erase(++it));
    }
  }

  // Query max(f(x)), time: O(log n)
  ll query(ll x) {
    assert(!S.empty());
    modeQ = 1;
    auto l = *S.lower_bound({ 0, 0, x });
    modeQ = 0;
    return l.a * x + l.b;
  }
};

bool LineContainer::modeQ = false;

struct Rect {
  int x, y; ll a;
  bool operator< (const Rect& b) const {
    return x < b.x;
  }
} a[maxn];

int n, que[maxn * 2];
ll dp[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%I64d", &a[i].x, &a[i].y, &a[i].a);
  }
  sort(a + 1, a + 1 + n);
  // LineContainer ch; ch.insert(0, 0);
  ll ans = 0;
  int ql = maxn, qr = maxn;
  a[0].x = a[0].y = 0; dp[0] = 0;
  auto eval = [&](int i, int y) -> ll {
    return -1ll * a[i].x * y + dp[i];
  };
  auto intersectX = [&](int i, int j) -> long double {
    return (long double)(dp[j] - dp[i]) / (a[j].x - a[i].x);
  };
  // query: desc; add: desc
  for (int i = 1; i <= n; i++) {
    // For query point y is desc, so convex hull on its right is useless 
    while (qr - ql >= 1 && eval(que[qr], a[i].y) <= eval(que[qr - 1], a[i].y)) {
      qr--;
    }
    dp[i] = 1ll * a[i].x * a[i].y - a[i].a;
    dp[i] += eval(que[qr], a[i].y);
    ans = max(ans, dp[i]);
    // maintain the conves hull by compare the intersect point x-cord
    while (qr - ql >= 1 && intersectX(i, que[ql]) >= intersectX(que[ql], que[ql + 1])) {
      ql++;
    }
    que[--ql] = i;
  }
  cout << ans << endl;
  return 0;
}