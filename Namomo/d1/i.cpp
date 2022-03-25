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

int n, f[maxn], g[maxn];
vector<int> edge[maxn];

void dfs(int u) {
  if (edge[u].size() == 0) {
    f[u] = 1;
    g[u] = 1;
    return ;
  }
  f[u] = 1;
  vector<int> val;
  for (int v: edge[u]) {
    dfs(v);
    val.push_back(f[v]);
    f[u] = mul(f[u], f[v]);
  }
  vector<int> pre(val.size(), 0), suf(val.size(), 0);
  for (int i = 0; i < val.size(); i++) {
    pre[i] = val[i];
    if (i) pre[i] = mul(pre[i], pre[i - 1]);
  }
  for (int i = (int)val.size() - 1; i >= 0; i--) {
    suf[i] = val[i];
    if (i + 1 < val.size()) suf[i] = mul(suf[i], suf[i + 1]);
  }
  for (int i = 0; i < val.size(); i++) {
    int cur = g[edge[u][i]];
    if (i) cur = mul(cur, pre[i - 1]);
    if (i + 1 < val.size()) cur = mul(cur, suf[i + 1]);
    f[u] = add(f[u], cur);
    g[u] = add(g[u], cur);
  }
  dbg(u, f[u], g[u]);
}

int main() {
  scanf("%d", &n);
  for (int i = 2, fa; i <= n; i++) {
    scanf("%d", &fa);
    edge[fa].push_back(i);
  }
  dfs(1);
  cout << f[1] << endl;
  return 0;
}