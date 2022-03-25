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

int n, L, a[maxn];

bool check(double T) {
  int v = 1;
  double len1 = 0, len2 = 0, rest = T;

  for (int i = 1; i <= n + 1; i++) {
    if (a[i] - a[i - 1] < rest * v) {
      rest -= (a[i] - a[i - 1]) / v;
      len1 += a[i] - a[i - 1];
      v++;
    } else {
      len1 += rest * v;
      break;
    }
  }

  v = 1;
  rest = T;
  for (int i = n; i >= 0; i--) {
    if (a[i + 1] - a[i] < rest * v) {
      rest -= (a[i + 1] - a[i]) / v;
      len2 += a[i + 1] - a[i];
      v++;
    } else {
      len2 += rest * v;
      break;
    }
  }

  // dbg(len1, len2);

  return len1 + len2 > L;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &L);
    a[n + 1] = L;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    double l = 0, r = inf, ans = inf;
    for (int i = 0; i < 400; i++) {
      double m = (l + r) / 2;
      if (check(m)) {
        ans = m;
        r = m;
      } else {
        l = m;
      }
    }
    printf("%.8lf\n", ans);
  }
  return 0;
}