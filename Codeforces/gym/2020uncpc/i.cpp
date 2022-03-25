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

int n, h[maxn], L[maxn], R[maxn], last[maxn];
ll dp[maxn];
vector<int> edge[maxn];

ll dfs(int u) {
  if (dp[u] != -1) return dp[u];
  dp[u] = 0;
  for (int v: edge[u]) {
    dfs(v);
    dp[u] = max(dp[u], dp[v] + abs(u - v));
  }
  return dp[u];
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", h + i);
  }

  vector<int> stk;
  for (int i = 1; i <= n; i++) {
    while (!stk.empty() && h[i] >= h[stk.back()]) {
      R[stk.back()] = i;
      stk.pop_back();
    }
    stk.push_back(i);
  }
  while (!stk.empty()) {
    R[stk.back()] = n + 1;
    stk.pop_back();
  }
  for (int i = 1; i <= n; i++) {
    last[i] = i;
  }
  for (int i = n; i >= 1; i--) {
    if (R[i] <= n && h[i] == h[R[i]]) {
      last[i] = last[R[i]];
      R[i] = R[R[i]];
    }
    if (R[i] <= n) {
      R[i] = last[R[i]];
    }
  }

  for (int i = n; i >= 1; i--) {
    while (!stk.empty() && h[i] >= h[stk.back()]) {
      L[stk.back()] = i;
      stk.pop_back();
    }
    stk.push_back(i);
  }
  while (!stk.empty()) {
    L[stk.back()] = 0;
    stk.pop_back();
  }
  for (int i = 1; i <= n; i++) {
    last[i] = i;
  }
  for (int i = 1; i <= n; i++) {
    if (L[i] >= 1 && h[i] == h[L[i]]) {
      last[i] = last[L[i]];
      L[i] = L[L[i]];
    }
    if (L[i] >= 1) {
      L[i] = last[L[i]];
    }
  }

  for (int i = 1; i <= n; i++) {
    dbg(i, L[i], R[i]);
    dp[i] = -1;
    if (L[i] >= 1) {
      edge[i].push_back(L[i]);
    }
    if (R[i] <= n) {
      edge[i].push_back(R[i]);
    }
  }

  for (int i = 1; i <= n; i++) {
    dfs(i);
  }

  for (int i = 1; i <= n; i++) {
    printf("%I64d ", dp[i]);
  }

  return 0;
}