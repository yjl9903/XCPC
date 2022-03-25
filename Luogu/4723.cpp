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
  #define dbg(args...) do { cout << "\033[32;1m" << #args << " -> ", err(args); } while(0)
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
const int mod = 1e9 + 7;
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

namespace LinearRecursive {
  // a[n] = r[0]a[n-1] + r[1]a[n-2] + r[2]a[n-3] + ... + r[m-1]a[n-m]
  // a[0] ~ a[m - 1]
  int cal(ll n, const vector<int>& r, const vector<int>& a) {
    if (n < (int)a.size()) return a[n];
    assert(r.size() == a.size());
    int m = (int)r.size();
    Poly md(m + 1, 0); md[m] = 1;
    for (int i = 0; i < m; i++) {
      md[m - i - 1] = sub(0, r[i]);
    }
    auto mulMod = [&](Poly a, Poly b) { // a * b % md
      int sa = (int)a.size(), sb = (int)b.size(), sz = sa + sb - 1;
      Poly ans(sz, 0);
      for (int i = 0; i < sa; i++) {
        for (int j = 0; j < sb; j++) {
          ans[i + j] = add(ans[i + j], mul(a[i], b[j]));
        }
      }
      if (sz < (int)md.size()) {
        return ans;
      }
      for (int i = sz - 1; i >= m; i--) {
        int tmp = ans[i];
        for (int j = i, k = m; k >= 0; k--, j--) {
          ans[j] = sub(ans[j], mul(md[k], tmp));
        }
      }
      return ans.resize(m), ans;
    };
    Poly f(1, 1), g(2, 0); g[1] = 1;
    while (n) {
      if (n & 1) f = mulMod(f, g);
      n >>= 1; g = mulMod(g, g);
    }
    int ans = 0;
    for (int i = 0; i < m; i++) ans = add(ans, mul(f[i], a[i]));
    return ans;
  }
}

int n, k;

int main() {
  scanf("%d%d", &n, &k);
  vector<int> f, a;
  for (int i = 0, x; i < k; i++) scanf("%d", &x), f.push_back((x % mod + mod) % mod);
  for (int i = 0, x; i < k; i++) scanf("%d", &x), a.push_back((x % mod + mod) % mod);
  printf("%d\n", LinearRecursive::cal(n, f, a));
  return 0;
}