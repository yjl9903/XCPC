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
#include <queue>
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
const int maxn = 500000 + 5;

int n, m, R, B, ord[maxn], a[maxn], key[maxn];
int vis[maxn], ans[maxn], deg[maxn], oud[maxn];
vector<int> edge[maxn];

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &n, &m, &R, &B);
    for (int i = 1; i <= n; i++) {
      key[i] = false;
      vis[i] = false;
      oud[i] = 0;
      ans[i] = 0;
      ord[i] = i;
      edge[i].clear();
    }
    for (int i = 1, x; i <= B; i++) {
      scanf("%d", &x);
      key[x] = true;
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    for (int i = 1, u, v; i <= m; i++) {
      scanf("%d%d", &u, &v);
      oud[u]++;
      edge[v].push_back(u);
    }
    sort(ord + 1, ord + 1 + n, [&](int x, int y) {
      return a[x] > a[y];
    });

    for (int i = 1; i <= n; i++) {
      int u = ord[i];
      int W = a[u];
      if (ans[u]) continue;
      queue<int> q;
      set<int> st;
      q.push(u);
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = i;
        ans[u] = max(ans[u], W);
        for (int v: edge[u]) {
          if (vis[v] == i) continue;
          if (key[v]) {
            q.push(v);
          } else {
            deg[v]++;
            st.insert(v);
            if (deg[v] == oud[v]) {
              q.push(v);
            }
          }
        }
      }
      // for (int x: st) deg[x] = 0;
    }

    printf("Case #%d:\n", ++kase);
    for (int i = 1; i <= n; i++) {
      printf("%d%c", ans[i], " \n"[i == n]);
    }
  }
  return 0;
}