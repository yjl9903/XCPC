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
const int maxn = 200000 + 5;

ll turn, L, R;

ll bs(ll x) {
  ll ans = -1, l = 1, r = 2e9;
  while (l <= r) {
    ll m = (l + r) / 2;
    if (x <= m * (m + 1) / 2) {
      ans = m;
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  assert(ans != -1);
  return ans;
}

pair<ll,ll> cal(ll x) {
  if (x == 0) return { 0ll, 0ll };
  ll sum = x * (x + 1) / 2;
  ll a = ((x + 1) / 2) * ((x + 1) / 2);
  return { a + turn * ((x + 1) / 2), sum - a + turn * (x - (x + 1) / 2) };
}

ll solve() {
  ll ans = 0, l = 0, r = 2e9;
  while (l <= r) {
    ll m = (l + r) / 2;
    auto tot = cal(m);
    if (L >= tot.first && R >= tot.second) {
      ans = m;
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  return ans;
}

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%lld%lld", &L, &R);
    turn = 0;
    if (L != R) {
      turn += bs(abs(R - L));
      if (L < R) {
        R -= turn * (turn + 1) / 2;
        while (R < 0 && turn >= 0) R += turn, turn--;
      } else {
        L -= turn * (turn + 1) / 2;
        while (L < 0 && turn >= 0) L += turn, turn--;
      }
    }
    dbg(L, R, turn);
    bool flag = false;
    if (L < R) {
      flag = true; swap(L, R);
    }
    ll turn2 = solve();
    dbg(turn2);
    auto tot = cal(turn2);
    L -= tot.first; R -= tot.second;
    if (flag) {
      swap(L, R);
    }
    printf("Case #%d: %lld %lld %lld\n", ++kase, turn + turn2, L, R);
  } 
  return 0;
}