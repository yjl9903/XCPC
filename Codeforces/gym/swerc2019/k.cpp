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
const int maxn = 100000 + 5;

int n, m, rt, is[maxn];
vector<int> edge[maxn];
set<int> ok[maxn];

int main() {
  scanf("%d%d%d", &n, &m, &rt);
  rt++;
  vector<int> key;
  for (int i = 1, u, v; i <= m; i++) {
    scanf("%d%d", &u, &v);
    u++; v++;
    if (v == rt) {
      key.push_back(u);
    } else {
      edge[v].push_back(u);
    }
  }
  for (int v: key) is[v] = 1;
  vector<int> ans;
  for (int u: key) {
    int x = u;
    function<void(int)> dfs = [&](int u) {
      if (ok[u].count(x) || (int)ok[u].size() > 1) return;
      ok[u].insert(x);
      for (int v: edge[u]) {
        dfs(v);
      }
    };
    dfs(u);
  }
  for (int v: key) if ((int)ok[v].size() == 1) ans.push_back(v);
  sort(begin(ans), end(ans));
  printf("%d\n", ans.size());
  for (int x: ans) {
    printf("%d\n", x - 1);
  }
  return 0;
}