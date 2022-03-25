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
const int maxn = 300000 + 5;

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

int n, m, f[maxn], g[maxn];
char buf[maxn];

int main() {
  g[0] = 1;
  for (int i = 1; i < maxn; i++) {
    g[i] = add(g[i - 1], g[i - 1]);
  }
  f[1] = 0;
  f[2] = 1;
  for (int i = 3; i < maxn; i++) {
    f[i] = add(f[i - 1], add(g[i - 2], add(f[i - 2], f[i - 2])));
  }
  scanf("%d%d", &n, &m);
  vector<string> allS;
  int ans = 0, sum = 0;
  for (int i = 0; i < n; i++) {
    scanf("%s", buf);
    allS.emplace_back(buf);
    for (int j = 0; j < m; j++) {
      if (buf[j] == 'o') {
        sum++;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    int cnt = 0;
    for (int j = 0; j <= m; j++) {
      if (j == m || allS[i][j] == '*') {
        ans = add(ans, mul(f[cnt], g[sum - cnt]));
        cnt = 0;
      } else {
        cnt++;
      }
    }
  }
  for (int j = 0; j < m; j++) {
    int cnt = 0;
    for (int i = 0; i <= n; i++) {
      if (i == n || allS[i][j] == '*') {
        ans = add(ans, mul(f[cnt], g[sum - cnt]));
        cnt = 0;
      } else {
        cnt++;
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}