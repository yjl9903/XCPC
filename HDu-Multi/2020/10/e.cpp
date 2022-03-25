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

int n, k, rt, dep[maxn], fa[maxn];
vector<int> edge[maxn];

void predfs(int u, int f) {
  if (dep[u] > dep[rt]) rt = u;
  for (int v: edge[u]) {
    if (v == f) continue;
    dep[v] = dep[u] + 1;
    predfs(v, u);
  }
}

void dfs(int u, int f) {
  fa[u] = f;
  for (int v: edge[u]) {
    if (v == f) continue;
    dep[v] = dep[u] + 1;
    dfs(v, u);
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
    }
    for (int i = 2, u, v; i <= n; i++) {
      scanf("%d%d", &u, &v);
      edge[u].push_back(v);
      edge[v].push_back(u);
    }
    dep[1] = 0;
    rt = 1;
    predfs(1, 0);
    dep[rt] = 0;
    dfs(rt, 0);
    int toR = rt;
    for (int i = 1; i <= n; i++) {
      if (dep[i] > dep[toR]) {
        toR = i;
      }
    }
    if (dep[toR] <= k) {
      puts("0");
      continue;
    }
    int u = toR;
    vector<int> vec;
    while (u) {
      vec.push_back(u);
      u = fa[u];
    }
    // for (int x: vec) dbg(x);
    auto solve = [&](int rt) {
      dep[rt] = 0;
      int ans = 0, flag = 0;
      function<int(int,int)> dfs = [&](int u, int f) {
        if (dep[u] > k / 2) ans++;
        int r = dep[u] == (k + 1) / 2;
        for (int v: edge[u]) {
          if (v == f) continue;
          dep[v] = dep[u] + 1;
          int cur = dfs(v, u);
          if (u == rt) {
            flag = max(flag, cur);
          } else {
            r += cur;
          }
        }
        return r;
      };
      dfs(rt, 0);
      // dbg(ans, flag);
      if (k % 2 == 0) {
        return ans;
      } else {
        return ans - flag;
      }
    };
    if (vec.size() % 2 == 1) {
      int rt = vec[vec.size() / 2];
      printf("%d\n", solve(rt));
    } else {
      int rt1 = vec[vec.size() / 2 - 1];
      int rt2 = vec[vec.size() / 2];
      dbg(rt1, rt2);
      printf("%d\n", min(solve(rt1), solve(rt2)));
    }
  }
  return 0;
}