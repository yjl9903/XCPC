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

int n, k, rt, ans, key[maxn], vis[maxn];
vector<PII> edge[maxn];
vector<int> stk;

void dfs(int u, int f) {
  stk.push_back(u);
  if (key[u]) {
    for (int i = (int)stk.size() - 1; i >= 0; i--) {
      int u = stk[i];
      if (!vis[u]) {
        vis[u] = true;
        ans++;
      } else {
        break;
      }
    }
  }
  for (auto& x: edge[u]) {
    int v = x.second;
    if (v == f) continue;
    dfs(v, u);
  }
  stk.pop_back();
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 2; i <= n; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    edge[u].emplace_back(w, v);
    edge[v].emplace_back(w, u);
  }
  for (int i = 1; i <= k; i++) {
    int x;
    scanf("%d", &x);
    key[x]++;
    rt = x;
  }
  dfs(rt, 0);
  printf("%d\n", ans);
  return 0;
}