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

int n, k, a[maxn];

struct BIT {
  int a[maxn];
  void update(int i, int x) {
    for (; i < maxn; i += i & -i) a[i] = add(a[i], x);
  }
  int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r = add(r, a[i]);
    return r;
  }
} dp[11];

int main() {
  scanf("%d%d", &n, &k);
  vector<int> lsh(1, 0);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    lsh.push_back(a[i]);
  }
  sort(begin(lsh), end(lsh));
  lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
  dp[0].update(1, 1);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    a[i] = lower_bound(begin(lsh), end(lsh), a[i]) - begin(lsh) + 1;
    for (int j = k - 1; j >= 0; j--) {
      int tot = dp[j].query(a[i] - 1);
      dp[j + 1].update(a[i], tot);
    }
  }
  printf("%d\n", dp[k].query(maxn - 1));
  return 0;
}