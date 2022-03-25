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

int n, m, k;
vector<int> edge[maxn];

bool vis[maxn];
int dep[maxn], fa[maxn], col[maxn];
vector<int> ring, ring2;
void dfs(int u, int f) {
  dbg(u, f);
  vis[u] = true;
  dep[u] = dep[f] + 1;
  fa[u] = f;
  for (int v: edge[u]) {
    if (v == f) continue;
    if (vis[v]) {
      int L = dep[u] - dep[v] + 1;
      if (L <= 2) continue;
      if (L <= k) {
        if (!ring.empty()) return ;
        int x = u;
        while (x && x != v) {
          dbg(x);
          ring.push_back(x);
          x = fa[x];
        }
        ring.push_back(v);
        break;
      } else if (ring2.empty()) {
        int x = u;
        while (x && x != v) {
          ring2.push_back(x);
          x = fa[x];
        }
        ring2.push_back(v);
      }
      continue;
    }
    dfs(v, u);
  }
  // vis[u] = false;
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1, u, v; i <= m; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  dfs(1, 0);
  if (!ring.empty()) {
    puts("2");
    printf("%d\n", ring.size());
    for (int x: ring) printf("%d ", x);
  } else {
    puts("1");
    if (!ring2.empty()) {
      for (int i = 0, j = 0; j < (k + 1) / 2; i += 2, j++) {
        assert(i < ring2.size());
        printf("%d ", ring2[i]);
      }
    } else {
      assert(m == n - 1);
      vector<int> bag[2];
      function<void(int,int)> dfs = [&](int u, int f) {
        col[u] = col[f] ^ 1;
        bag[col[u]].push_back(u);
        for (int v: edge[u]) {
          if (v == f) continue;
          dfs(v, u);
        }
      };
      dfs(1, 0);
      vector<int> ans;
      if (bag[0].size() > bag[1].size()) {
        ans = bag[0];
      } else {
        ans = bag[1];
      }
      assert(ans.size() >= (k + 1) / 2);
      ans.resize((k + 1) / 2);
      for (int x: ans) printf("%d ", x);
    }
  }
  puts("");
  return 0;
}