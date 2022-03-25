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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

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

int n, f[maxn];

int main() {
  cin >> n;
  f[0] = 1;
  for (int i = 1; i <= n; i++) f[i] = mul(10, f[i - 1]);
  for (int i = 1; i < n; i++) {
    int ans = mul(2 * 10 * 9, f[n - i - 1]);
    if (n - i - 2 >= 0) {
      ans = add(ans, mul(f[n - i - 2], mul(n - i - 1, 10 * 9 * 9)));
    }
    printf("%d ", ans);
  }
  printf("%d\n", 10);
  return 0;
}