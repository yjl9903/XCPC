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
const int maxn = 1000000 + 5;

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

int n, f[maxn], g[maxn];
// vector<int> edge[maxn];

struct Edge {
  int nxt, to;
} e[maxn * 2];
int ecnt, head[maxn];
void adde(int u, int v) {
  e[++ecnt] = { head[u], v };
  head[u] = ecnt;
}

void dfs(int u, int ff) {
  f[u] = g[u] = 1;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].to;
    if (v == ff) continue;
    dfs(v, u);
    f[u] = mul(f[u], add(g[v], f[v]));
    g[u] = add(g[u], sub(add(g[v], f[v]), 1));
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    adde(u, v); adde(v, u);
  }
  dfs(1, 0);
  // for (int i = 1; i <= n; i++) {
  //   dbg(i, f[i], g[i]);
  // }
  printf("%d\n", add(f[1], g[1]));
  return 0;
}