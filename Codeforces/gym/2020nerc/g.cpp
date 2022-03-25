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
const int maxn = 100 + 5;

int n, k, siz[maxn];
vector<int> edge[maxn];

struct Trans {
  int u, k, S;
} pre[maxn][maxn][maxn][2];

int f[maxn][maxn][maxn][2], g[maxn][maxn][2];
void dfs(int u, int ff) {
  siz[u] = 1;
  f[u][u][1][0] = f[u][u][1][1] = 0;
  pre[u][u][1][0] = pre[u][u][1][1] = { 0, 0, 0 };
  int last = u;
  for (int v: edge[u]) {
    if (v == ff) continue;
    dfs(v, u);
    for (int i = 1; i <= siz[u] + siz[v]; i++) {
      f[u][v][i][0] = f[u][last][i][0];
      f[u][v][i][1] = f[u][last][i][1];
      pre[u][v][i][0] = { last, i, 0 };
      pre[u][v][i][1] = { last, i, 1 };
    }
    for (int i = siz[u]; i >= 1; i--) {
      for (int j = siz[v]; j >= 1; j--) {
        if (f[u][last][i][0] + g[v][j][1] + 2 < f[u][v][i + j][0]) {
          f[u][v][i + j][0] = f[u][last][i][0] + g[v][j][1] + 2;
          pre[u][v][i + j][0] = { last, i, 0 };
        }
        if (f[u][last][i][1] + g[v][j][0] + 1 < f[u][v][i + j][0]) {
          f[u][v][i + j][0] = f[u][last][i][1] + g[v][j][0] + 1;
          pre[u][v][i + j][0] = { last, i, 1 };
        }
        if (f[u][last][i][1] + g[v][j][1] + 2 < f[u][v][i + j][1]) {
          f[u][v][i + j][1] = f[u][last][i][1] + g[v][j][1] + 2;
          pre[u][v][i + j][1] = { last, i, 1 };
        }
      }
    }
    siz[u] += siz[v];
    last = v;
  }
  for (int i = 1; i <= siz[u]; i++) {
    g[u][i][0] = f[u][last][i][0];
    g[u][i][1] = f[u][last][i][1];
  }
}

void walk(vector<int>& ans, int sum, int u, int ff) {
  function<void(int,int)> dfs = [&](int u, int f) {
    sum--;
    if (sum == 0) return ;
    for (int v: edge[u]) {
      if (v == f) continue;
      ans.push_back(v);
      dfs(v, u);
      ans.push_back(u);
      if (sum == 0) return ;
    }
  };
  ans.push_back(u);
  dfs(u, ff);
}

vector<int> solve(int k, int u, int ff) {
  vector<int> ans { u };
  vector<PII> full;
  int chooseU = -1, chooseK = -1;
  int x = -1, S = 0;
  for (int v: edge[u]) {
    if (v == ff) continue;
    x = v;
  }
  // dbg(k, u);
  while (x != -1 && x != u) {
    auto trans = pre[u][x][k][S];
    // dbg(x, k, S);
    // dbg(trans.u, trans.k, trans.S);
    if (S == 0) {
      if (trans.S == 1) {
        if (trans.k < k) {
          chooseU = x;
          chooseK = k - trans.k;
        }
        x = trans.u;
        k = trans.k;
        S = 1;
      } else {
        full.emplace_back(x, k - trans.k);
        x = trans.u;
        k = trans.k;
      }
    } else {
      assert(trans.S == 1);
      full.emplace_back(x, k - trans.k);
      x = trans.u;
      k = trans.k;
    }
  }
  
  for (auto x: full) {
    if (x.second == 0) continue;
    // dbg(x.first, x.second, u);
    walk(ans, x.second, x.first, u);
    ans.push_back(u);
  }
  if (chooseU == -1) {
    assert(k == 1);
  } else {
    for (int x: solve(chooseK, chooseU, u)) {
      ans.push_back(x);
    }
  }
  return ans;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
    }
    for (int i = 2, f; i <= n; i++) {
      scanf("%d", &f);
      edge[f].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        for (int k = 1; k <= n; k++) {
          f[i][j][k][0] = f[i][j][k][1] = inf;
        }
      }
    }
    dfs(1, 0);
    printf("%d\n", g[1][k][0]);
    auto ans = solve(k, 1, -1);
    for (int x: ans) {
      printf("%d ", x);
    }
    puts("");
  }
  return 0;
}