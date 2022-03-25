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
const int maxn = 5000 + 5;

int n, m, f[maxn][maxn];
vector<PII> bag[maxn];

int dfs(int l, int r) {
  if (l > r) return 0;
  if (f[l][r] != -1) return f[l][r];
  int ans = 0, cnt = 0;
  if (l < r) {
    ans = max(dfs(l + 1, r), dfs(l, r - 1));
  }
  for (auto& x: bag[l]) {
    int y = x.first;
    if (y < r) {
      int cur = dfs(l, y) + dfs(y + 1, r);
      // dbg(l, r, y, cur);
      ans = max(ans, cur);
    } else if (y == r) {
      cnt = x.second;
    }
  }
  return f[l][r] = ans + cnt;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      bag[i].clear();
      for (int j = 1; j <= n; j++) {
        f[i][j] = -1;
      }
    }
    map<PII,int> mp;
    for (int i = 1; i <= m; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      mp[{ x, y }]++;
    }
    for (auto& x: mp) {
      bag[x.first.first].emplace_back(x.first.second, x.second);
    }
    printf("%d\n", dfs(1, n));
  }
  return 0;
}