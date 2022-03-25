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

int n, k, a[maxn];

int main() {
  scanf("%d%d", &n, &k);
  vector<PII> v;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    v.emplace_back(a[i], i);
  }
  sort(begin(v), end(v), greater<PII>());
  vector<int> pos;
  ll sum = 0;
  int ans = 1;
  for (int i = 0; i < k; i++) pos.push_back(v[i].second), sum += v[i].first;
  sort(begin(pos), end(pos));
  for (int i = 1; i < k; i++) {
    ans = mul(ans, pos[i] - pos[i - 1]);
  }
  printf("%I64d %d", sum, ans);
  return 0;
}