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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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
const int maxn = 5000 + 5;

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

int n, a[maxn], _inv[maxn * maxn];
int f[maxn][maxn];
int pf[maxn][maxn], pfs[maxn][maxn];
int ph[maxn][maxn], phs[maxn][maxn];

int inv(int x) {
  if (x < maxn * maxn) {
    return _inv[x];
  } else {
    return qpow(x, mod - 2);
  }
}

int main() {
  _inv[1] = 1;
  for (int i = 2; i < maxn * maxn; i++)
    _inv[i] = (mod - mod / i) * 1ll * _inv[mod % i] % mod;

  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }

  int sum = 0, cnt = 0;
  for (int i = n + 1; i >= 1; i--) {
    for (int j = n; j >= 0; j--) {
      pf[i][j] = pf[i + 1][j];
      pfs[i][j] = pfs[i + 1][j];
      ph[i][j] = ph[i][j + 1];
      phs[i][j] = phs[i][j + 1];

      if (i == j) continue;
      if (i == n + 1 && j == 0) continue;

      int cur = 0;
      if (i == n + 1 || a[i] < a[j]) {
        cur = add(cur, 1);
        if (pfs[i][j] > 0) {
          cur = add(cur, mul(pf[i][j], inv(pfs[i][j])));
        }

        ph[i][j] = add(ph[i][j], cur);
        phs[i][j]++;
      } else {
        cur = add(cur, 1);
        if (phs[i][j] > 0) {
          cur = add(cur, mul(ph[i][j], inv(phs[i][j])));
        }

        pf[i][j] = add(pf[i][j], cur);
        pfs[i][j]++;
      }
      f[i][j] = cur;

      if (j == 0) {
        sum = add(sum, cur);
        cnt++;
      }
    }
  }
  
  int ans = mul(sum, inv(cnt));
  printf("%d\n", ans);
  return 0;
}