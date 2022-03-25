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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

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

int n, m;

int main() {
  cin >> n >> m;
  int s1 = mul(2 * m - 2, mul(n - 2, n));
  int s2 = mul(2 * n - 2, mul(m - 2, m));
  int s3 = mul(2 * m - 4, mul(n - 1, n));
  int s4 = mul(2 * n - 4, mul(m - 1, m));
  int s5 = mul(2 * n - 2, mul(m - 2, 2));
  int s6 = mul(2 * m - 2, mul(n - 2, 2));
  int ans = add(add(s1, s2), add(s3, s4));
  ans = sub(ans, s5);
  ans = sub(ans, s6);
  cout << ans << endl;
  return 0;
}