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

ll a, m, g;
vector<ll> pri;

ll solve(ll n) {
  n /= g;
  ll ans = 0;
  int ss = 1 << pri.size();
  for (int s = 1; s < ss; s++) {
    ll tmp = 1, c = 0;
    for (int i = 0; i < (int)pri.size(); i++) {   
      if (s >> i & 1) {
        tmp *= pri[i]; c++;
      }
    }
    ans += (c & 1 ? n / tmp : -n / tmp);
  }
  return n - ans;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    pri.clear();
    scanf("%I64d%I64d", &a, &m);
    g = __gcd(a, m);
    ll x = m / g;
    for (ll i = 2; 1ll * i * i <= x; i++) {
      if (x % i) continue;
      pri.push_back(i);
      while (x % i == 0) x /= i;
    }
    if (x > 1) pri.push_back(x);
    printf("%I64d\n", solve(a + m - 1) - solve(a - 1));
  }
  return 0;
}