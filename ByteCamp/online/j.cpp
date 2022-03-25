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

int ans, up[maxn], dp[maxn][maxn];
void dfs(int u) {
  if (up[u]) {
    dp[u][dep[u] - dep[up[u]]] = 1;
  } else {
    dp[u][0] = 1;
  }
  for (int v: edge[u]) {
    dfs(v);
    vector<int> tmp(n + 1, 0);
    int sum = 0, all = 0;
    for (int i = 0; i <= n; i++) all = add(all, dp[v][i]);
    for (int i = n; i >= 2; i--) {
      sum = add(sum, dp[u][i]);
      tmp[i - 1] = mul(sum, dp[v][i]);
    }
    sum = 0;
    for (int i = n - 1; i >= 1; i--) {
      sum = add(sum, dp[v][i + 1]);
      tmp[i] = add(tmp[i], mul(dp[u][i], sum));
      tmp[i] = add(tmp[i], mul(all, dp[u][i]));
      tmp[i] = add(tmp[i], mul(dp[v][0], dp[u][i]));
      if (i > 1) {
        tmp[i - 1] = add(tmp[i - 1], mul(dp[u][0], dp[v][i]));
      }
    }
    tmp[0] = add(tmp[0], mul(dp[u][0], dp[v][0]));
    tmp[0] = add(tmp[0], mul(dp[u][0], all));
    for (int i = 0; i <= n; i++) dp[u][i] = tmp[i];
  }
  dbg(u);
  for (int i = 0; i <= n; i++) {
    dbg(i, dp[u][i]);
  }
  dp[u][1] = 0;
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
  printf("%d\n", dp[1][0]);
  return 0;
}