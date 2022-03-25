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
const int maxn = 1000000 + 5;

int n;
vector<int> edge[maxn];
set<int> dir[maxn];

int sum[maxn][2], fa[maxn];
bool flag[maxn][2];
void predfs(int u, int f) {
  fa[u] = f;
  sum[u][0] = sum[u][1] = 0;
  flag[u][0] = flag[u][1] = 0;
  for (int v: edge[u]) {
    if (v == f) continue;
    predfs(v, u);
    int t = dir[u].count(v);
    sum[u][t] += sum[v][t];
  }
  if (sum[u][0] == 0) {
    sum[u][0] = 1;
    flag[u][0] = 1;
  }
  if (sum[u][1] == 0) {
    sum[u][1] = 1;
    flag[u][1] = 1;
  }
}
int rsum[maxn][2], ans, rt;
void dfs(int u, int f) {
  dbg(u, rsum[u][0], rsum[u][1]);
  if (rsum[u][0] + rsum[u][1] - 2 < ans) {
    ans = rsum[u][0] + rsum[u][1] - 2;
    rt = u;
  }
  for (int v: edge[u]) {
    if (v == f) continue;

    int tot[2] = { rsum[u][0] - sum[v][0], rsum[u][1] - sum[v][1] };

    if (flag[v][0]) {
      if (dir[u].count(v)) {
        rsum[v][0] = 1;
      } else {
        rsum[v][0] = tot[0];
      }
    } else {
      rsum[v][0] = sum[v][0] + tot[0];
    }

    if (flag[v][1]) {
      if (!dir[u].count(v)) {
        rsum[v][1] = 1;
      } else {
        rsum[v][1] = tot[1];
      }
    } else {
      rsum[v][1] = sum[v][1] + tot[1];
    }
    
    dfs(v, u);
  }
}

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      edge[i].clear(); dir[i].clear();
    }
    for (int i = 2, u, v; i <= n; i++) {
      scanf("%d%d", &u, &v);
      edge[u].push_back(v);
      edge[v].push_back(u);
      dir[u].insert(v);
    }
    predfs(1, 0);
    rsum[1][0] = sum[1][0];
    rsum[1][1] = sum[1][1];
    ans = n + 1;
    dfs(1, 0);
  }
  return 0;
}