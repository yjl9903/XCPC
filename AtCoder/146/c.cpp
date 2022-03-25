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
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
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

ll a, b, x;

ll cal(ll x) {
  ll ans = a * x;
  while (x) {
    ans += b;
    x /= 10;
  }
  return ans;
}

int main() {
  cin >> a >> b >> x;
  ll l = 1, r = 1e9, ans = 0;
  while (l <= r) {
    ll m = (l + r) / 2;
    if (cal(m) <= x) ans = m, l = m + 1;
    else r = m - 1;
  }
  cout << ans;
  return 0;
}