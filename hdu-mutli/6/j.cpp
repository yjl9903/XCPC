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
const int maxn = 100 + 5;

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

namespace Gause {
  int a[maxn][maxn];
  void clear() {
    ms(a, 0);
  }
  int solve(int n) {
    int res = 1;
    for (int i = 1; i <= n; i++) {
      int qaq = qpow(a[i][i], mod - 2);
      for (int j = i + 1; j <= n; j++) {
        int tmp = 1ll * a[j][i] * qaq % mod;
        for (int k = 1; k <= n; k++)
          a[j][k] = (a[j][k] - 1ll * a[i][k] * tmp % mod + mod) % mod;
      }
    }
    for (int i = 1; i <= n; i++) res = 1ll * res * a[i][i] % mod;
    return res;
  }
}

int n, m, a[maxn * maxn], b[maxn * maxn], c[maxn * maxn], deg[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    Gause::clear();
    for (int i = 1; i <= m; i++) {
      scanf("%d%d%d", a + i, b + i, c + i);
      int u = a[i], v = b[i];
      Gause::a[u][v]--;
      Gause::a[v][u]--;
      Gause::a[u][u]++;
      Gause::a[v][v]++;
    }
    int fm = Gause::solve(n - 1);
    if (fm == 0) {
      puts("0");
    } else {
      int ans = 0;
      for (int j = 0; j < 30; j++) {
        Gause::clear();
        ms(deg, 0);
        int cnt = 0;
        for (int i = 1; i <= m; i++) {
          if (c[i] >> j & 1) {
            int u = a[i], v = b[i];
            Gause::a[u][v]--;
            Gause::a[v][u]--;
            Gause::a[u][u]++;
            Gause::a[v][v]++;

            deg[u]++;
            deg[v]++;
            if (deg[u] == 1) cnt++;
            if (deg[v] == 1) cnt++;
          }
        }
        if (cnt == n) {
          int r = Gause::solve(n - 1);
          ans = add(ans, mul(qpow(2, j), r));
        }
      }
      ans = mul(ans, inv(fm));
      printf("%d\n", ans);
    }
  }
  return 0;
}