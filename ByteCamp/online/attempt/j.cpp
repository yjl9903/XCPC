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
  #define dbg(args...) cout << #args << " -> ", err(args)
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
const int mod = 228228239;
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

int n, m, dep[maxn], siz[maxn];
vector<int> edge[maxn];

void getdep(int u) {
  siz[u] = 1;
  for (int v: edge[u]) {
    dep[v] = dep[u] + 1;
    getdep(v);
    siz[u] += siz[v];
  }
}

int ans, up[maxn], dp[maxn][maxn][2];
void dfs(int u) {
  if (up[u]) {
    for (int i = 0; i <= dep[up[u]]; i++) {
      dp[u][i][1] = qpow(2, siz[u]);
    }
  }
  if (edge[u].empty()) {
    for (int i = 0; i <= dep[u]; i++) {
      dp[u][i][0] = 2;
    }
  } else {
    for (int i = 0; i <= dep[u]; i++) {
      dp[u][i][0] = 2;
    }
  }
  int sizsum = 1;
  for (int v: edge[u]) {
    dfs(v);
    for (int i = 0; i <= dep[u]; i++) {
      int dp0 = dp[u][i][0], dp1 = dp[u][i][1];
      // dbg(u, i);
      // dbg(dp0, dp[v][i][0]);
      // dbg(dp1, dp[v][i][1]);
      // dp[u][i][0] = add(dp[u][i][0], mul(dp0, dp[v][i][0]));
      // dp[u][i][0] = add(dp[u][i][0], mul(dp0, qpow(2, siz[v])));
      // dp[u][i][0] = add(dp[u][i][0], mul(dp1, dp[v][i][1]));
      // dp[u][i][1] = add(dp[u][i][1], mul(dp0, dp[v][i][1]));
      // dp[u][i][1] = add(dp[u][i][1], mul(dp1, dp[v][i][0]));
      // dp[u][i][1] = add(dp[u][i][1], mul(dp1, qpow(2, siz[v])));
      int r0 = 0, r1 = 0;
      r0 = add(r0, mul(dp0, dp[v][i][0]));
      r0 = add(r0, mul(dp0, qpow(2, siz[v])));
      r0 = add(r0, mul(dp1, dp[v][i][1]));
      r1 = add(r1, mul(sub(dp0, qpow(2, sizsum)), dp[v][i][1]));
      r1 = add(r1, mul(dp1, dp[v][i][0]));
      r1 = add(r1, mul(dp1, qpow(2, siz[v])));
      dp[u][i][0] = r0;
      dp[u][i][1] = r1;
      // dbg(dp[u][i][0], dp[u][i][1]);
    }
    sizsum += siz[v];
  }
  for (int i = 0; i <= dep[u]; i++) {
    dp[u][i][0] = sub(dp[u][i][0], qpow(2, siz[u]));
    // dp[u][i][1] = mul(dp[u][i][1], inv(2));
  }
  dbg(u);
  for (int i = 0; i <= dep[u]; i++) {
    dbg(i, dp[u][i][0], dp[u][i][1]);
  }
  for (int i = 0; i <= dep[u]; i++) {
    int dp0 = sub(dp[u][i][0], dp[u][i + 1][0]);
    int dp1 = sub(dp[u][i][1], dp[u][i + 1][1]);
    ans = add(ans, mul(qpow(2, i), dp1));
    ans = sub(ans, mul(qpow(2, i), dp0));
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 2, fa; i <= n; i++) {
    scanf("%d", &fa);
    edge[fa].push_back(i);
  }
  getdep(1);
  scanf("%d", &m);
  for (int i = 1, u, v; i <= m; i++) {
    scanf("%d%d", &u, &v);
    if (!up[v] || dep[u] > dep[up[v]] ) {
      up[v] = u;
    }
  }
  for (int i = 2; i <= n; i++) {
    if (up[i] && dep[i] == dep[up[i]] + 1) {
      puts("0"); return 0;
    }
  }
  dfs(1);
  printf("%d\n", sub(qpow(2, n - 1), ans));
  return 0;
}