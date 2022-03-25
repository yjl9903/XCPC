#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
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

int n, k, d[maxn];

int calr(int n) {
  int ans = qpow(k, n - n / 2);
  if (n % 2 == 1) {
    ans = add(ans, mul(n - 1, qpow(k, n / 2 + 1)));
  } else {
    ans = add(ans, mul(n / 2, qpow(k, n / 2 + 1)));
    ans = add(ans, mul(n / 2 - 1, qpow(k, n / 2)));
  }
  return ans;
}

int main() {
  cin >> n >> k;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    vector<int> v = { 1 };
    for (int j = 2; 1ll * j * j <= i; j++) {
      if (i % j) continue;
      v.push_back(j);
      if (1ll * j * j != i) v.push_back(i / j);
    }
    int tot = calr(i);
    for (auto l: v) {
      tot = sub(tot, mul(i / l, d[l]));
      ans = add(ans, d[l]);
    }
    ans = add(ans, tot);
    d[i] = tot;
    cout << i << " : " << d[i] << endl;
  }
  cout << ans;
  return 0;
}