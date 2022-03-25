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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int add(int a, int b, int c) {
  return add(a, add(b, c));
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

int n, f[maxn], g[maxn], h[maxn];
vector<int> edge[maxn];

void dfs(int u, int ff) {
  f[u] = g[u] = h[u] = 1;
  for (int v: edge[u]) {
    if (v == ff) continue;
    dfs(v, u);
    f[u] = mul(f[u], sub(add(2ll * f[v] % mod, 2ll * g[v] % mod), h[v]));
    g[u] = mul(g[u], sub(add(2ll * f[v] % mod, g[v] % mod), h[v]));
    h[u] = mul(h[u], sub(add(f[v] % mod, g[v] % mod), h[v]));
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  dfs(1, 0);
  int ans = sub(add(f[1], sub(g[1], h[1])), 1);
  cout << ans << endl;
  return 0;
}