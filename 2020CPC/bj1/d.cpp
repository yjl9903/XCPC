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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

int n, m, flag[maxn], lonely[maxn];
vector<int> edge[maxn];

int tot, dfn[maxn], low[maxn], fa[maxn];
void dfs(int p, int old) {
  dfn[p] = low[p] = ++tot;
  int cnt = old != 0;
  for (int v: edge[p]) {
    if (v == old) continue;
    if (!dfn[v]) {
      fa[v] = p;
      dfs(v, p);
      low[p] = min(low[p], low[v]);
      cnt += low[v] >= dfn[p];
    } else {
      low[p] = min(low[p], dfn[v]);
    }
  }
  dbg(p, cnt);
  if (cnt > 1) {
    flag[p] = cnt - 1;
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (!dfn[i]) {
      int st = tot;
      dfs(i, 0);
      if (tot - st == 1) {
        lonely[i] = true;
      }
      ans++;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (lonely[i]) {
      printf("%d ", ans - 1);
    } else if (flag[i]) {
      printf("%d ", ans + flag[i]);
    } else {
      printf("%d ", ans);
    }
  }
  return 0;
}