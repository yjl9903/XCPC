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
#include <queue>
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
const int maxn = 2000 + 5;

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
  int S(int n, int m) {
    // x_1 + x_2 + ... + x_n = m, x_i >= 0
    if (n == 0 && m == 0) return 1;
    return C(m + n - 1, n - 1);
  }
  int H(int n) {
    // Catalan
    return sub(C(2 * n, n), C(2 * n, n - 1));
  }
}
using Comb::C;

namespace acam {
  static const int maxp = 100000 + 5;
  static const int S = 26;
  static const int Base = 'a';
  int sz, ch[maxp][S], fail[maxp], val[maxp];
  int node() {
    ms(ch[++sz], 0);
    fail[sz] = val[sz] = 0;
    return sz;
  }
  void clear() {
    sz = 0; node();
    for (int i = 0; i < S; i++) ch[0][i] = 1;
  }
  int insert(char* s, int i) {
    int u = 1;
    for (int i = 0; s[i]; i++) {
      int v = s[i] - Base; // !
      if (!ch[u][v]) ch[u][v] = node();
      u = ch[u][v];
    }
    val[u] += i;
    return u;
  }
  vector<int> edge[maxp];
  void build() {
    queue<int> q; q.push(1);
    while (!q.empty()) {
      int t = q.front(); q.pop();
      for (int i = 0; i < S; i++) {
        if (ch[t][i]) {
          fail[ch[t][i]] = ch[fail[t]][i];
          q.push(ch[t][i]);
        } else {
          ch[t][i] = ch[fail[t]][i];
        }
      }
    }
    for (int i = 2; i <= sz; i++) edge[fail[i]].push_back(i);
    function<void(int)> dfs = [&](int u) {
      for (int v: edge[u]) {
        val[v] += val[u]; dfs(v);
      }
    };
    dfs(1);
  }
}

int n, m, c[maxn];
int f[maxn][maxn], f2[maxn][maxn], g[maxn][maxn], g2[maxn][maxn];
char s[maxn];

int main() {
  Comb::init();
  acam::clear();
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%s%d", s, c + i);
    acam::insert(s, c[i]);
  }
  acam::build();
  g2[1][1] = 1;
  for (int i = 1; i <= m; i++) {
    for (int u = 1; u <= acam::sz; u++) {
      for (int v = 1; v <= acam::sz; u++) {
        for (int c = 0; c < 26; c++) {
          int nx = acam::ch[u][c];
          
        }
      }
    }
  }
  int ans = 0;
  for (int u = 1; u <= acam::sz; u++) {
    for (int v = 1; v <= acam::sz; v++) {
      ans = add(ans, f[u][v]);
    }
  }
  cout << ans << endl;
  return 0;
}