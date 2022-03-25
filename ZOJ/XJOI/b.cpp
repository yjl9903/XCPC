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
const int maxn = 50000 + 5;

int n, a[maxn], ans = 0;
vector<int> edge[maxn];

int vis[maxn], siz[maxn], sum, mn, rt;
void getrt(int u, int f) {
  siz[u] = 1; int t = 0;
  for (int v: edge[u]) {
    if (v == f || vis[v]) continue;
    getrt(v, u); siz[u] += siz[v];
    t = max(t, siz[v]);
  }
  t = max(t, sum - siz[u]);
  if (t < mn) mn = t, rt = u;
}
int getrt(int u) {
  sum = siz[u]; mn = 1e9; rt = 0;
  getrt(u, 0); return rt;
}

void solve(int u) {
  vis[u] = 1;
  int mx = 0, val = a[u];
  function<void(int)> handle = [&](int v) {
    int tmx = 0;
    function<void(int,int,int)> dfs = [&](int u, int f, int d) {
      tmx = max(tmx, d);
      ans = max(ans, d * val);
      ans = max(ans, a[u] * (d + mx));
      for (int v: edge[u]) {
        if (v == f || vis[v]) continue;
        dfs(v, u, d + 1);
      }
    };
    dfs(v, u, 1);
    mx = max(mx, tmx);
  };
  for (int v: edge[u]) {
    if (vis[v]) continue;
    handle(v);
  }
  reverse(begin(edge[u]), end(edge[u]));
  mx = 0;
  for (int v: edge[u]) {
    if (vis[v]) continue;
    handle(v);
  }
  for (int v: edge[u]) {
    if (vis[v]) continue;
    solve(getrt(v));
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 2, u , v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  siz[1] = n;
  solve(getrt(1));
  printf("%d\n", ans);
  return 0;
}