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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, dep[maxn];
ll f[maxn], g[maxn];
vector<int> edge[maxn];

void dfs(int u) {
  f[u] = g[u] = 0;
  for (int v: edge[u]) {
    dep[v] = dep[u] + 1;
    dfs(v);
    g[u] += min(2 + g[v], 1 + dep[u] + f[v]);
  }
  f[u] = g[u];
  for (int v: edge[u]) {
    ll cur = g[u] - min(2 + g[v], 1 + dep[u] + f[v]);
    f[u] = min(f[u], cur + 1 + f[v]);
  }
}

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
    }
    for (int i = 2, f; i <= n; i++) {
      scanf("%d", &f);
      edge[f].push_back(i);
    }
    ll ans = 0;
    for (int v: edge[1]) {
      dep[v] = 1;
      dfs(v);
      ans += 1 + f[v];
    }
    printf("Case #%d: %lld\n", ++kase, ans);
  }
  return 0;
}