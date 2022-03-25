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
const int maxn = 200000 + 5;
const int A = 10007;
const int B = 18980504;

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

int ST = 3000;
vector<int> edge[maxn];
PII comp[maxn];
bool vis[maxn];

void dfs(int u) {
  if (vis[u]) return ;
  vis[u] = 1;
  int v1 = edge[u][0], v2 = edge[u][1];
  dfs(v1); dfs(v2);
  int ta = add(comp[v2].first, mul(comp[v2].second, comp[v1].first));
  int tb = mul(comp[v2].second, comp[v1].second);
  comp[u] = { ta, tb };
  dbg(u, ta, tb);
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  int x, u, v;
  while (cin >> x >> u >> v) {
    edge[x].push_back(u);
    edge[x].push_back(v);
  }
  vis[0] = vis[1] = 1;
  comp[0] = { 0, A };
  comp[1] = { B, 1 };
  dfs(ST);
  dbg(comp[ST].first, comp[ST].second);
  return 0;
}