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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 500 + 5;

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

struct Mat {
  static const int M = 201;
  ll a[M][M];
  Mat() { ms(a, 0); }
  void clear() { ms(a, 0); }
  void eye() { for (int i = 0; i < M; i++) a[i][i] = 1; }
  ll* operator [] (int x) { return a[x]; }
  const ll* operator [] (int x) const { return a[x]; }
  Mat operator * (const Mat& b) {
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
  Mat operator + (const Mat& b) {
    const Mat& a = *this; Mat r;
    for (int i = 0; i < M; i++)
      for (int j = 0; j < M; j++)
        r[i][j] = (a[i][j] + b[i][j]) % mod;
    return r;
  }
  void print() const {
    #ifdef XLor
      for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++)
          printf("%lld%c", (*this)[i][j], " \n"[j == M - 1]);
    #endif
  }
} f, trans;

int n, m, k, p[maxn];

int main() {
  scanf("%d%d%d", &n, &k, &m);
  int sum = 0;
  for (int i = 1; i <= k; i++) {
    if (i % m) {
      p[i % m]++;
      sum++;
    }
  }
  int ivs = inv(sum);
  // dbg(sum);
  for (int i = 0; i < m; i++) p[i] = mul(p[i], ivs);
  f[0][0] = 1;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      trans[i][j] = p[(i + m - j) % m];
    }
  }
  // trans.print();
  printf("%d\n", (f * trans.pow(n))[0][0]);
  return 0;
}