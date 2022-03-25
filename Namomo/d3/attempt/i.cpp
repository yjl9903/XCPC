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
  #define dbg(args...) cout << "" << #args << " -> ", err(args)
  void err() { std::cout << "" << std::endl; }
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
const int maxn = 2000 + 5;

int n, k, a[maxn];
bool vis[maxn][maxn];
double g[maxn], f[maxn][maxn];

double cal(int i, int j) {
  double cur = 0;
  for (int k = j, p = (i + j - 1) / j - 1; p >= 0; k += j, p--) {
    int len = j;
    if (p == 0) len = i - (k - j);
    // dbg(len, i, p, a[p]);
    cur += 1.0 * len / i * a[p];
  }
  // dbg(cur);
  return cur;
}

int main() {
  int rp, rc;
  scanf("%d%d%d", &rp, &rc, &k);
  n = rc - rp;
  for (int i = 0; i <= k; i++) {
    scanf("%d", a + i);
  }
  g[1] = 0.0;
  g[2] = (a[0] + a[1]) / 2.0;
  for (int i = 3; i <= n; i++) {
    if (i <= k + 1) {
      g[i] = 0.0;
      for (int j = 1; j <= i; j++) {
        g[i] += 1.0 * a[i - j];
      }
      g[i] /= i;
    } else {
      g[i] = 1e18;
    }
    // dbg(i, g[i]);
    for (int j = 2; j < i; j++) {
      if ((i + j - 1) / j <= k + 1) {
        f[i][j] = cal(i, j);
        dbg(i, j);
        if (i % j == 0) {
          f[i][j] += g[j];
        } else {
          f[i][j] += 1.0 * (i - i % j) / i * g[j];
          f[i][j] += 1.0 * (i % j) / i * g[i % j];
        }
        dbg(cal(i, j), f[i][j]);
        // dbg(i, j, f[i][j]);
        g[i] = min(g[i], f[i][j]);
      }
    }
    dbg(i, g[i]);
  }
  printf("%.8lf\n", g[n]);
  return 0;
}