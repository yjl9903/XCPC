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
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, m, s, a[maxn];
vector<int> edge[maxn], edge2[maxn]; 

int cnt, bel[maxn];
ll sum[maxn], num[maxn];
namespace Tarjan {
  int tot, dfn[maxn], low[maxn], st[maxn], top, vis[maxn];
  void dfs(int u, int f) {
    dfn[u] = low[u] = ++tot;
    st[++top] = u; vis[u] = 1;
    int k = 0;
    for (int& v: edge[u]) {
      if (v == f && !k) {
        k++; continue;
      }
      if (!dfn[v]) {
        dfs(v, u); low[u] = min(low[u], low[v]);
      } else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
      cnt++; int t = 0;
      do {
        t = st[top--];
        bel[t] = cnt;
        vis[t] = 0;
      } while (t != u);
    }
  }
  void scc(int n, vector<int> * g) {
    for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(i, 0);
    for (int i = 1; i <= n; i++) g[i].clear();
    for (int i = 1; i <= n; i++) {
      int u = bel[i];
      sum[u] += a[i]; num[u]++;
      for (int& x: edge[i]) {
        int v = bel[x];
        if (u != v) {
          g[u].push_back(v);
        }
      }
    }
  }
}

ll dp[maxn][2]; bool back[maxn];
void dfs(int u, int f) {
  dp[u][0] = sum[u];
  back[u] = num[u] > 1;
  for (int v: edge2[u]) {
    if (v == f) continue;
    dfs(v, u); back[u] |= back[v];
    if (back[v]) {
      dp[u][0] += dp[v][0];
    }
  }
  dp[u][1] = dp[u][0];
  for (int v: edge2[u]) {
    if (v == f) continue;
    if (back[v]) {
      dp[u][1] = max(dp[u][1], dp[u][0] - dp[v][0] + dp[v][1]);
    } else {
      dp[u][1] = max(dp[u][1], dp[u][0] + dp[v][1]);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 1, u, v; i <= m; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  scanf("%d", &s);
  Tarjan::scc(n, edge2);
  dfs(bel[s], 0);
  printf("%I64d\n", dp[bel[s]][1]);
  return 0;
}