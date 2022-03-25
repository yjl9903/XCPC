#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
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
const int maxn = 50000 + 5;

int n;
ll k, c[maxn];

int check(ll mid) {
  ll sum = 0, last = 0;
  for (int i = 1; i <= n; i++) {
    ll tot = last + c[i];
    sum += tot / mid;
    // last = tot % mid;
    last = min(tot % mid, c[i]);
    if (sum >= k) return 1;
  }
  return sum >= k;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%I64d", &n, &k);  
    for (int i = 1; i <= n; i++) scanf("%I64d", c + i);
    ll l = 1, r = 5e12, ans = 0;
    while (l <= r) {
      ll m = (l + r) / 2;
      if (check(m)) ans = m, l = m + 1;
      else r = m - 1;
    }
    printf("%I64d\n", ans * k);
  }
  return 0;
}