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

int n, q;
vector<int> edge[maxn];
ll val[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
      val[i] = 0;
    }
    for (int i = 2, u, v; i <= n; i++) {
      scanf("%d%d", &u, &v);
      edge[u].push_back(v);
      edge[v].push_back(u);
    }
    
    for (int i = 1; i <= q; i++) {
      int op, u, w;
      function<void(int,int,int)> dfs = [&](int u, int f, int d) {
        val[u] += w - d;
        for (int v: edge[u]) {
          if (v == f) continue;
          dfs(v, u, d + 1);
        }
      };
      scanf("%d%d", &op, &u);
      if (op == 1) {
        scanf("%d", &w);
        dfs(u, 0, 0);
      } else if (op == 2) {
        val[u] = 0;
      } else if (op == 3) {
        printf("%lld\n", val[u]);
      }
    }
  }
  return 0;
}