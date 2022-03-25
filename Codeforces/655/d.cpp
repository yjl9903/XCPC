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

int n, a[maxn * 3];

int main() {
  scanf("%d", &n);
  ll sum = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    sum += a[i];
    a[i + n] = a[i];
    a[i + n + n] = a[i];
  }
  if (n == 1) {
    printf("%d\n", a[1]);
    return 0;
  }
  ll tot = 0;
  for (int i = 1; i <= n / 2; i++) {
    tot += a[i + i - 1];
  }
  ll ans = tot;
  for (int i = 3; i <= n + n; i += 2) {
    tot -= a[i - 2];
    tot += a[i + n - 3];
    ans = min(ans, tot);
  }
  printf("%I64d\n", sum - ans);
  return 0;
}