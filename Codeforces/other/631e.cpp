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
#include <limits>
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

struct LineContainer  {
  static const ll inf = 2e18;
  static bool modeQ;
 
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

  // Insert f(x) = ax + b
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

  // Query max(f(x))
  ll query(ll x) {
    assert(!S.empty());
    modeQ = 1;
    auto l = *S.lower_bound({ 0, 0, x });
    modeQ = 0;
    return l.a * x + l.b;
  }
};

bool LineContainer::modeQ = false;

int n, a[maxn];
ll all, sum[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    sum[i] = a[i] + sum[i - 1];
    all += 1ll * i * a[i];
  }
  ll ans = all;
  LineContainer ch; ch.insert(a[1], 0);
  for (int i = 2; i <= n; i++) {
    ans = max(ans, all - sum[i] + ch.query(i));
    ch.insert(a[i], sum[i] - 1ll * i * a[i]);
  }
  ch.clear(); ch.insert(1, 0);
  for (int i = 2; i <= n; i++) {
    ans = max(ans, all + sum[i - 1] - 1ll * i * a[i] + ch.query(a[i]));
    ch.insert(i, -sum[i - 1]);
  }
  cout << ans << endl;
  return 0;
}