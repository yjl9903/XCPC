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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

namespace ModOpe {
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
}
using namespace ModOpe;

using Poly = vector<int>;

namespace PolyOpe {
  #ifdef XLor
    #define print(a) cout << "\033[32;1m" << #a << " -> ", err(a)
    void err(const Poly& a) {
      std::cout << "[ ";
      for (auto& x: a) std::cout << x << ' ';
      std::cout << "]\033[39;0m" << std::endl;
    }
  #else
    #define print(a)
  #endif

  int rev[maxn << 3], aa[maxn << 3], bb[maxn << 3];
  inline int build(int m) {
    int step = 0, n = 1;
    for (; n < m; n <<= 1) ++step;
    for (int i = 1; i < n; i++)
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (step - 1));
    return n;  
  }

  inline void ntt(int a[], int n, int op = 0) {
    for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int h = 2; h <= n; h <<= 1) {
      int wn = qpow(3, (mod - 1) / h);
      if (op == -1) wn = inv(wn);
      for (int i = 0; i < n; i += h) {
        int w = 1;
        for (int j = i; j < i + h / 2; j++) {
          int u = a[j], t = 1ll * a[j + h / 2] * w % mod;
          a[j] = (u + t) % mod;
          a[j + h / 2] = (u - t + mod) % mod;
          w = 1ll * w * wn % mod;
        }
      }
    }
    if (op == -1) {
      ll rn = inv(n);
      for (int i = 0; i < n; i++) a[i] = 1ll * a[i] * rn % mod;
    }
  }
  inline Poly operator * (const Poly& a, const Poly& b) {
    int lim = build((int)a.size() + (int)b.size() - 1);
    for (int i = 0; i < (int)a.size(); i++) aa[i] = a[i];
    for (int i = (int)a.size(); i < lim; i++) aa[i] = 0;
    for (int i = 0; i < (int)b.size(); i++) bb[i] = b[i];
    for (int i = (int)b.size(); i < lim; i++) bb[i] = 0;
    ntt(aa, lim); ntt(bb, lim);
    for (int i = 0; i < lim; i++) aa[i] = 1ll * aa[i] * bb[i] % mod;
    ntt(aa, lim, -1);
    Poly ans;
    for (int i = 0; i < (int)a.size() + (int)b.size() - 1; i++) 
      ans.push_back(aa[i]);
    return ans;
  }
  inline Poly inv(const Poly& f) {
    Poly g(1, ModOpe::inv(f[0]));
    for (int len = 2; (len >> 1) < (int)f.size(); len <<= 1) {
      int lim = build(len + len);
      for (int i = 0; i < len; i++) aa[i] = i < (int)f.size() ? f[i] : 0;
      for (int i = len; i < lim; i++) aa[i] = 0;
      for (int i = 0; i < len; i++) bb[i] = i < (int)g.size() ? g[i] : 0;
      for (int i = len; i < lim; i++) bb[i] = 0;
      ntt(aa, lim); ntt(bb, lim);
      for (int i = 0; i < lim; i++) {
        aa[i] = mul(bb[i], sub(2, mul(aa[i], bb[i])));
      }
      ntt(aa, lim, -1); g.resize(len);
      for (int i = 0; i < len; i++) g[i] = aa[i];
    }
    return g.resize(f.size()), g;
  }
  inline Poly operator + (Poly f, const Poly& g) {
    f.resize(max(f.size(), g.size()));
    for (int i = 0; i < (int)g.size(); i++) {
      f[i] = add(f[i], g[i]);
    }
    return f;
  }
  inline Poly operator - (Poly f, const Poly& g) {
    f.resize(max(f.size(), g.size()));
    for (int i = 0; i < (int)g.size(); i++) {
      f[i] = sub(f[i], g[i]);
    }
    return f;
  }
  inline Poly operator / (Poly f, Poly g) {
    int sz = (int)f.size() - (int)g.size() + 1;
    reverse(begin(f), end(f)); f.resize(sz);
    reverse(begin(g), end(g)); g.resize(sz);
    f = f * inv(g);
    f.resize(sz); reverse(begin(f), end(f)); 
    return f;
  }
  inline Poly operator % (Poly f, Poly g) {
    Poly r = f - f / g * g;
    return r.resize(g.size() - 1), r;
  }
}
using namespace PolyOpe;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  Poly f, g;
  for (int i = 0, x; i <= n; i++) {
    scanf("%d", &x); f.push_back(x);
  }
  for (int i = 0, x; i <= m; i++) {
    scanf("%d", &x); g.push_back(x);
  }
  auto q = f / g;
  for (auto& x: q) printf("%d ", x);
  puts("");
  auto r = f % g;
  for (auto& x: r) printf("%d ", x);
  puts("");
  return 0;
}