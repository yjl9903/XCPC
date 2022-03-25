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
const int maxn = 100 + 5;

int n, a[maxn], b[maxn];
ll f[maxn][maxn * maxn], g[maxn][maxn * maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", a + i, b + i);
  }
  ms(f, -1);
  f[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    ms(g, -1);
    for (int j = 0; j < i; j++) {
      for (int s = 0; s < maxn * maxn; s++) {
        if (f[j][s] < 0) continue;
        if (s + a[i] < maxn * maxn) {
          g[j + 1][s + a[i]] = max(g[j + 1][s + a[i]], f[j][s] + 2ll * b[i]);
        }
        g[j][s] = max(g[j][s], f[j][s] + b[i]);
      }
    }
    // dbg(i);
    // for (int s = 0; s <= 20; s++) {
    //   dbg(g[1][s]);
    // }
    swap(f, g);
  }
  for (int i = 1; i <= n; i++) {
    ll ans = 0;
    for (int j = 0; j < maxn * maxn; j++) {
      // dbg(i, j, f[i][j]);
      ans = max(ans, min(f[i][j], 2ll * j));
    }
    printf("%.12lf ", ans / 2.0);
  }
  return 0;
}