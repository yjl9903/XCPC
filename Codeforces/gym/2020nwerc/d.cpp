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
#include <random>
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
  { 300000, 777777 }, { 30000, 1000 },
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

const vector<PII> dir {
  { -1, -1 }, { -1, 1 },
  { 1, -1 }, { 1, 1 }
};
mt19937 rnd(time(nullptr));
uniform_int_distribution<> gen(0, 1000000);

int main() {
  scanf("%d", &n);
  vector< pair<ll,ll> > vec;
  while (n > 0) {
    int x = gen(rnd);
    int y = gen(rnd);
    ll res = query(x, y);
    if (res == 0) {
      n--;
      continue;
    }
    ll sq = sqrt(res);
    vec.clear();
    for (ll i = 0; i <= sq; i++) {
      ll yy = res - i * i;
      ll q = sqrt(yy);
      if (q * q == yy) {
        for (auto& d: dir) {
          {
            ll a = x + d.first * i;
            ll b = y + d.second * q;
            if (0 <= a && a <= 1000000) {
              if (0 <= b && b <= 1000000) {
                vec.emplace_back(a, b);
              }
            }
          }
          {
            ll a = x + d.first * q;
            ll b = y + d.second * i;
            if (0 <= a && a <= 1000000) {
              if (0 <= b && b <= 1000000) {
                vec.emplace_back(a, b);
              }
            }
          }
        }
      }
    }
    dbg(n, x, y, res, vec.size());
    if (!vec.empty() && vec.size() <= 100) {
      for (auto& x: vec) {
        ll res = query(x.first, x.second);
        if (res == 0) {
          n--;
          break;
        }
      }
      for (int i = 0; i < 7; i++) dbg(i, vis[i]);
    }
  }
  dbg(cnt);
  return 0;
}