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
#include <queue>
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

int n, a[maxn], deg[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    map<int,set<int> > edge;
    map<int,set<int> > mex;
    auto link = [&](int u, int v) {
      if (u == v) return ;
      if (u > v) swap(u, v);
      edge[u].insert(v);
    };
    link(a[1], a[n]);
    for (int i = 2; i <= n; i++) {
      link(a[i], a[i - 1]);
    }
    set<int> vis;
    for (int i = 1; i <= n; i++) {
      if (vis.count(a[i])) continue;
      vis.insert(a[i]);
      for (int x: edge[a[i]]) {
        deg[x]++;
      }
    }
    map<int,int> ans;
    vis.clear();
    for (int i = 1; i <= n; i++) if (deg[a[i]] == 0) vis.insert(a[i]), ans[a[i]] = 1;
    queue<int> q;
    for (int x: vis) q.push(x);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v: edge[u]) {
        mex[v].insert(ans[u]);
        deg[v]--;
        if (deg[v] == 0) {
          int tot = 1;
          for (int x: mex[v]) {
            if (x == tot) {
              tot++;
            } else {
              break;
            }
          }
          ans[v] = tot;
          q.push(v);
        }
      }
    }
    int k = 1;
    for (auto x: ans) k = max(k, x.second);
    printf("%d\n", k);
    for (int i = 1; i <= n; i++) {
      printf("%d ", ans[a[i]]);
    }
    puts("");
  }
  return 0;
}