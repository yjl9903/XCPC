#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
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

namespace Comb {
  const int maxc = 2000000 + 5;
  int f[maxc], inv[maxc], finv[maxc];
  void init() {
    inv[1] = 1;
    for (int i = 2; i < maxc; i++)
      inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
    f[0] = finv[0] = 1;
    for (int i = 1; i < maxc; i++) {
      f[i] = f[i - 1] * 1ll * i % mod;
      finv[i] = finv[i - 1] * 1ll * inv[i] % mod;
    }
  }
  int C(int n, int m) {
    if (m < 0 || m > n) return 0;
    return f[n] * 1ll * finv[n - m] % mod * finv[m] % mod;
  }
}
using Comb::C;

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
}
using namespace PolyOpe;

int n, nn, l[maxn], r[maxn];
int a[maxn], pre[maxn];
int g[maxn], f[maxn];

int main() {
  Comb::init();
  scanf("%d", &n);
  vector<int> lsh;
  auto gid = [&](int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
  };

  for (int i = 1; i <= n; i++) {
    scanf("%d%d", l + i, r + i);
    lsh.push_back(l[i]);
    lsh.push_back(r[i]);
  }
  sort(lsh.begin(), lsh.end());
  lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
  nn = lsh.size();
  for (int i = 1; i <= n; i++) {
    int L = gid(l[i]);
    int R = gid(r[i]);
    pre[L]++;
    pre[R]--;
  }
  int all = 0;
  for (int i = 1; i < nn; i++) {
    pre[i] += pre[i - 1];
    assert(0 <= pre[i] && pre[i] <= n);
    a[n - pre[i]] = add(a[n - pre[i]], lsh[i] - lsh[i - 1]);
    all = add(all, lsh[i] - lsh[i - 1]);
  }

  Poly x, y;
  for (int i = 0; i <= n; i++) {
    x.push_back(mul(a[i], Comb::f[i]));
    y.push_back(Comb::finv[n - i]);
  }
  Poly res = x * y;
  
  for (int k = 0; k <= n; k++) {
    f[k] = add(f[k], mul(all, C(n, k)));
    f[k] = sub(f[k], mul(Comb::finv[k], res[n + k]));
    f[k] = mul(f[k], Comb::f[k]);
    f[k] = mul(f[k], Comb::f[n - k]);
  }

  ms(pre, 0);
  lsh.clear();
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", l + i, r + i);
    lsh.push_back(l[i]);
    lsh.push_back(r[i]);
  }
  sort(lsh.begin(), lsh.end());
  lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
  nn = lsh.size();
  for (int i = 1; i <= n; i++) {
    int L = gid(l[i]);
    int R = gid(r[i]);
    pre[L]++;
    pre[R]--;
  }
  int ans = 0;
  for (int i = 1; i < nn; i++) {
    pre[i] += pre[i - 1];
    assert(0 <= pre[i] && pre[i] <= n);
    ans = add(ans, mul(lsh[i] - lsh[i - 1], f[pre[i]]));
  }
  ans = mul(ans, Comb::finv[n]);
  printf("%d\n", ans);
  return 0;
}