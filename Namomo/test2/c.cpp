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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

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

int n, a[maxn];

namespace Solve2 {
  int dp[20][maxn];
  void build() {
    for (int i = 1; i <= n; i++) dp[0][i] = i;
    for (int j = 1; j < 20; j++)
      for (int i = 1; i + (1 << j) <= n + 1; i++) {
        int l = dp[j - 1][i];
        int r = dp[j - 1][i + (1 << (j - 1))];
        if (a[l] < a[r]) dp[j][i] = l;
        else dp[j][i] = r;
      }
  }
  int qmin(int l, int r) {
    int k = __lg(r - l + 1);
    int x = dp[k][l], y = dp[k][r - (1 << k) + 1];
    if (a[x] < a[y]) return x;
    else return y;
  }

  int cal(int l, int r, int base) {
    if (l == r) {
      return a[l] - base;
    } else if (l > r) {
      return 0;
    }
    int pos = qmin(l, r);
    int nbase = a[pos];
    int sum = mul(nbase - base, mul(r - l + 1, r - l + 1));
    sum = add(sum, cal(l, pos - 1, nbase));
    while (pos < r) {
      int npos = qmin(pos + 1, r);
      if (a[npos] > nbase) break;
      sum = add(sum, cal(pos + 1, npos - 1, nbase));
      pos = npos;
    }
    sum = add(sum, cal(pos + 1, r, nbase));
    return sum;
  }

  int solve() {
    build();
    return cal(1, n, 0);
  }
}

namespace Solve1 {
  int solve() {
    int ans = 0;
    for (int i = 1; i <= n; ) {
      int j = i + 1;
      while (j <= n && a[j] >= a[j - 1]) {
        j++;
      }
      
      i = j;
    }
    return ans;
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  
  cout << Solve1::solve() << ' ' << Solve2::solve() << endl;
  return 0;
}