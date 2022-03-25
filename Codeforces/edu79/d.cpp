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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
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

int n, cnt[maxn];
vector<int> bag[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int k, x; scanf("%d", &k);
    while (k--) {
      scanf("%d", &x); bag[i].push_back(x);
      cnt[x]++;
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int ivk = inv(bag[i].size());
    for (int x: bag[i]) {
      ans = add(ans, mul(cnt[x], ivk));
    }
  }
  cout << mul(ans, qpow(inv(n), 2));
  return 0;
}