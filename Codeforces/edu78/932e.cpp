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
const int mod = 1e9 + 7;
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
inline int inv(int x) {
  return qpow(x, mod - 2);
}

int n, k, S[maxn][maxn];

int main() {
  cin >> n >> k;
  S[0][0] = 1;
  for (int i = 1; i <= k; i++) {
    for (int j = 1; j <= k; j++) {
      S[i][j] = add(S[i - 1][j - 1], mul(S[i - 1][j], j));
    }
  }
  int ans = 0, f = 1;
  for (int i = 1; i <= k && i <= n; i++) {
    f = mul(f, n + 1 - i);
    int tmp = mul(f, qpow(2, n - i));
    tmp = mul(tmp, S[k][i]);
    ans = add(ans, tmp);
  }
  cout << ans << endl;
  return 0;
}