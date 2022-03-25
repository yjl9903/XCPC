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

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
  return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}
inline int inv(int x) {
  return qpow(x, mod - 2);
}

ll D;
vector<ll> divs;
int q, f[maxn], finv[maxn];

map<ll,int> norm(ll x) {
  map<ll,int> mp;
  for (auto& d: divs) {
    if (x % d) continue;
    int c = 0;
    while (x % d == 0) x /= d, c++;
    mp[d] = c;
  }
  return mp;
}

int main() {
  f[0] = finv[0] = 1;
  for (int i = 1; i < maxn; i++) {
    f[i] = mul(i, f[i - 1]);
    finv[i] = mul(inv(i), finv[i - 1]);
  }
  scanf("%I64d", &D);
  for (ll i = 2; i * i <= D; i++) {
    if (D % i) continue;
    while (D % i == 0) D /= i;
    divs.push_back(i);
  }
  if (D > 1) {
    divs.push_back(D);
  }
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    ll u, v; scanf("%I64d%I64d", &u, &v);
    auto vec1 = norm(u), vec2 = norm(v);
    int ans = 1, sub = 0, add = 0;
    for (auto& x: vec1) {
      if (vec2.count(x.first)) {
        if (x.second > vec2[x.first]) {
          sub += x.second - vec2[x.first];
          ans = mul(ans, finv[x.second - vec2[x.first]]);
        }
      } else {
        sub += x.second;
        ans = mul(ans, finv[x.second]);
      }
    }
    for (auto& x: vec2) {
      if (vec1.count(x.first)) {
        if (x.second > vec1[x.first]) {
          add += x.second - vec1[x.first];
          ans = mul(ans, finv[x.second - vec1[x.first]]);
        }
      } else {
        add += x.second;
        ans = mul(ans, finv[x.second]);
      }
    }
    dbg(sub, add);
    printf("%d\n", mul(ans, mul(f[add], f[sub])));
  }
  return 0;
}