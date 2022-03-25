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

int m, cnt[20], pre[20], siz[20];

int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }

int main() {
  for (int i = 1; i <= 4; i++) scanf("%d", cnt + i);
  for (int i = 1; i <= 12; i++) pre[i] = i, siz[i] = 1;
  scanf("%d", &m);
  for (int i = 1, u, v; i <= m; i++) {
    scanf("%d%d", &u, &v);
    u = find(u); v = find(v);
    if (u != v) {
      pre[u] = v; siz[v] += siz[u];
    }
  }
  vector<int> vec;
  for (int i = 1; i <= 12; i++) {
    if (i == find(i)) {
      vec.push_back(siz[i]);
    }
  }
  int ans = 0;
  function<void(int)> dfs = [&](int u) {
    if (u == (int)vec.size()) {
      ans++;
      return ;
    }
    for (int i = 1; i <= 4; i++) {
      if (cnt[i] >= vec[u]) {
        cnt[i] -= vec[u];
        dfs(u + 1);
        cnt[i] += vec[u];
      }
    }
  };
  dfs(0);
  printf("%d\n", ans);
  return 0;
}