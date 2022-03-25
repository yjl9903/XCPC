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
const int maxn = 200000 + 5;

int n, a[maxn], fa[maxn];
vector<int> edge[maxn];

bool vis[maxn];
ll val[maxn], val2[maxn];
vector<int> p1, p2;

ll dfs(int u) {
  if (vis[u]) {
    return val[u];
  }
  ll& sum = val[u];
  sum = a[u];
  for (int v: edge[u]) {
    sum += dfs(v);
  }
  vis[u] = true;
  if (sum >= 0) {
    if (u) {
      p1.push_back(u);
    }
    return sum;
  } else {
    if (u) {
      p2.push_back(u);
    }
    return 0;
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", fa + i);
    if (fa[i] == -1) {
      edge[0].push_back(i);
    } else {
      edge[fa[i]].push_back(i);
    }
  }
  dfs(0);
  for (int i = 1; i <= n; i++) {
    dbg(i, val[i]);
  }
  vector<int> plan = p1;
  reverse(begin(p2), end(p2));
  for (int x: p2) plan.push_back(x);
  for (int i = 1; i <= n; i++) val2[i] = a[i];
  ll ans = 0;
  for (int x: plan) {
    ans += val2[x];
    if (fa[x] != -1) {
      val2[fa[x]] += val2[x];
    }
  }
  printf("%lld\n", ans);
  for (int x: plan) printf("%d ", x);
  return 0;
}