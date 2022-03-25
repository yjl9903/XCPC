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

int n, a[maxn], b[maxn];

struct Tree {
  int n, rt;
  vector< vector<int> > edge;
  vector<int> dep, fa, key;

  void dfs(int u, int f) {
    if (rt == -1 || dep[u] > dep[rt]) {
      rt = u;
    }
    for (int v: edge[u]) {
      if (v == f) continue;
      dep[v] = dep[u] + 1;
      fa[v] = u;
      dfs(v, u);
    }
  }

  int read(int id) {
    scanf("%d", &n);
    edge.assign(n + 1, vector<int>());
    dep.assign(n + 1, 0);
    fa.assign(n + 1, 0);
    key.assign(n + 1, 0);
    for (int i = 2; i <= n; i++) {
      int f;
      scanf("%d", &f);
      edge[f].push_back(i);
      edge[i].push_back(f);
    }
    rt = -1;
    dep[1] = 0;
    dfs(1, 0);
    assert(rt != -1);
    int x = rt;
    rt = -1;
    dep[x] = 0;
    fa[x] = 0;
    dfs(x, 0);
    assert(rt != -1);
    int y = rt, len = dep[rt];
    {
      vector<int> vec;
      int x = y;
      while (x) {
        vec.push_back(x);
        key[x] = true;
        x = fa[x];
      }
      assert(vec.size() == len + 1);
      int ans = 0;
      for (int x: vec) {
        dep[x] = 0;
        cur = 0;
        dfs2(x, 0);
        ans = max(ans, cur);
      }
      b[id] = ans;
    }
    return len;
  }

  int cur;
  void dfs2(int u, int f) {
    cur = max(cur, dep[u]);
    for (int v: edge[u]) {
      if (v == f || key[v]) continue;
      dep[v] = dep[u] + 1;
      dfs2(v, u);
    }
  }
} tr[maxn];

int main() {
  while (scanf("%d", &n) == 1) {
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
      a[i] = tr[i].read(i);
      dbg(i, a[i], b[i]);
      ans += a[i];
      ans += b[i];
    }
    printf("%lld\n", 2ll * ans);
  }
  return 0;
}