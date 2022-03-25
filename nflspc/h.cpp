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
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
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

int n, m, k;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &m, &k);
    int ans = qpow(k, n + m - 1);
    // for (int i = 0; i < n + m - 1; i++) {
    //   int tot = qpow(k - 1, min(i, n + m - 2 - i));
    //   ans = mul(ans, tot);
    // }
    ll sum = 0;
    if (n > m) swap(n, m);
    if (n == 1) {
      printf("%d\n", ans);
      continue;
    }
    sum += 1ll * n * (n - 1) / 2;
    sum += 1ll * (n - 1) * (m - n);
    sum += 1ll * (n - 1) * (n - 2) / 2;
    ans = mul(ans, qpow(k - 1, sum));
    printf("%d\n", ans);
  }
  return 0;
}