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
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
using Poly = vector<int>;
const int mod = 1000000007;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

inline ll qpow(ll x, ll n) {
  x %= mod;
  ll r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r % mod;
}

ll n, x, y, a, b;

struct Mat {
  static const int M = 3;
  __int128 a[M][M];
  Mat() { ms(a, 0); }
  void clear() { ms(a, 0); }
  void eye() { for (int i = 0; i < M; i++) a[i][i] = 1; }
  __int128* operator [] (int x) { return a[x]; }
  const __int128* operator [] (int x) const { return a[x]; }
  Mat operator * (const Mat& b) {
    int mod = 1e9 + 6;
    const Mat& a = *this; Mat r;
    for (int i = 0; i < M; i++)
      for (int j = 0; j < M; j++)
        for (int k = 0; k < M; k++)
          r[i][j] = (r[i][j] + a[i][k] * b[k][j]) % mod;
    return r;
  }
  Mat pow(ll n) const {
    Mat a = *this, r; r.eye();
    while (n > 0) {
      if (n & 1)  r = r * a;
      n >>= 1; a = a * a;
    }
    return r;
  }
};

int main() {
  cin >> n >> x >> y >> a >> b;
  if (n == 1) {
    cout << x << endl;
    return 0;
  } else if (n == 2) {
    cout << y << endl;
    return 0;
  }

  Mat f, s;
  f[0][0] = f[0][1] = f[0][2] = f[1][0] = f[2][2] = 1;

  f = f.pow(n - 2);

  s[1][0] = 1;
  ll s1 = qpow(x, (long long)((f * s)[0][0] % (mod - 1)));

  s[1][0] = 0;
  s[0][0] = 1;
  ll s2 = qpow(y, (long long)((f * s)[0][0] % (mod - 1)));

  s[0][0] = 0;
  s[2][0] = b % (mod - 1);
  ll s3 = qpow(a, (long long)((f * s)[0][0] % (mod - 1)));

  dbg(s1, s2, s3);

  cout << s1 * s2 % mod * s3 % mod << endl;

  return 0;
}