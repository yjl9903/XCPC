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

int n, m, a[maxn];

int C(int n, int m) {
  if (n >= m) {
    int ans = 1;
    for (int i = 0; i < m; i++) {
      ans = mul(ans, n - i);
      ans = mul(ans, inv(i + 1));
    }
    return ans;
  } else {
    return 0;
  }
}

int main() {
  scanf("%d%d", &n, &m);
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    sum += a[i];
  }
  cout << C(n + m, n + sum) << endl;
  return 0;
}