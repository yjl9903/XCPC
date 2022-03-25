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
const int mod = 1e9 + 7;
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

int n, f[maxn], g[maxn], h[maxn];
vector<int> edge[maxn];

void dfs(int u, int ff) {
  // int sz = (int)edge[u].size() - (u == 1 ? 0 : 1);
  // if (sz == 0) {
  //   f[u] = 0; g[u] = h[u] = 1;
  //   return ;
  // }
  int sum = 0, sum2 = 0;
  int pif = 1, pifg = 1;
  for (int v: edge[u]) {
    if (v == ff) continue;
    dfs(v, u);
    int tot = mul(h[v], inv(add(f[v], g[v])));
    sum = add(sum, tot);
    sum2 = add(sum2, mul(tot, tot));
    pif = mul(pif, f[v]);
    pifg = mul(pifg, add(f[v], g[v]));
  }
  sum = sub(mul(sum, sum), sum2);
  f[u] = mul(inv(2), mul(pifg, sum));
  g[u] = h[u] = pif;
  for (int v: edge[u]) {
    if (v == ff) continue;
    g[u] = add(g[u], mul(h[v], mul(pif, inv(f[v]))));
    h[u] = add(h[u], mul(h[v], mul(pifg, inv(add(f[v], g[v])))));
  }
  dbg(u, f[u], g[u], h[u]);
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  dfs(1, 0);
  cout << add(f[1], g[1]) << endl;
  return 0;
}