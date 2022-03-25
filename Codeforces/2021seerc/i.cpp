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
const int maxn = 1000000 + 5;

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

int n, f[maxn], vis[maxn];
vector<int> divsor[maxn];

int main() {
  scanf("%d", &n);
  if (n == 1) return puts("1"), 0;
  if (n == 2) return puts("2"), 0;
  if (n == 3) return puts("6"), 0;
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) {
      divsor[j].push_back(i);
    }
  }
  f[3] = 1;
  for (int i = 4; i <= n; i++) {
    vis[i] = i;
    for (int j = 0; j <= 2; j++) {
      for (int x: divsor[i - j]) {
        if (vis[x] != i) {
          vis[x] = i;
          f[i] = add(f[i], f[x]);
        }
      }
    }
  }
  int ans = 0;
  for (int i = 0; i <= n; i++) {
    ans = add(ans, f[i]);
  }
  printf("%d\n", mul(ans, 2 * n));
  return 0;
}