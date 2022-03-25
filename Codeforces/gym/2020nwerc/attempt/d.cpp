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
#include <cstdlib>
#include <ctime>
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
const int maxn = 200000 + 5;

const double delta = 0.82;
const double eps = 1e-7;

ll sqr(ll x) {
  return x * x;
}

int n, cnt = 0;

bool vis[16];
vector<PII> points {
  { 1000, 1000 }, { 2000, 2000 },
  { 1000, 2000 }, { 2000, 1000 },
  { 300000, 30000 }, { 30000, 1000 },
  { 99999, 6666 }
};

ll query(int x, int y) {
  cnt++;
  #ifdef ONLINE_JUDGE
    cout << x << " " << y << endl;
    ll r; cin >> r;
    return r;
  #else
    ll r = inf;
    for (int i = 0; i < points.size(); i++) {
      if (vis[i]) continue;
      ll cur = sqr(x - points[i].first) + sqr(y - points[i].second);
      if (cur == 0) {
        vis[i] = true;
        return 0;
      }
      r = min(r, cur);
    }
    return r;
  #endif
}

bool bin() {
  int l = 0, r = 1e6;
  ll res = inf;
  while (l < r) {
    int ml = l + (r - l) / 3;
    int mr = r - (r - l) / 3;
    ll x = query(ml, 0);
    if (x == 0) return true;
    ll y = query(mr, 0);
    if (y == 0) return true;
    if (x < y) {
      res = min(res, x);
      r = mr - 1;
    } else {
      res = min(res, y);
      l = ml + 1;
    }
  }
  if (res == inf) {
    return false;
  } else {
    return query(l, (int)sqrt(res)) == 0;
  }
}

bool solve() {
  int x = (int)5e5;
  int ansx = x;
  double t = 5e5;
  ll ans = 1e16;
  while (t > eps) {
    int tx = x + ((rand() << 1) - RAND_MAX) * t;
    if (tx <= 0) tx = 0;
    if (tx >= 1000000) tx = 1000000;
    ll now = query(tx, 0);
    if (now == 0) {
      return true;
    }
    ll d = now - ans;
    if (d < 0) {
      x = tx;
      ansx = tx;
      ans = now;
    } else if (exp(-1.0 * d / t) * RAND_MAX > rand()) {
      x = tx;
    }
    t *= delta;
  }
  return query(ansx, (int)sqrt(ans)) == 0;
}

int main() {
  srand(time(NULL));
  scanf("%d", &n);
  while (n > 0) {
    if (n == 1) {
      bool r = bin();
      assert(r);
      n--;
    } else {
      bool r = solve();
      assert(r);
      n--;
    }
  }
  dbg(cnt);
  return 0;
}