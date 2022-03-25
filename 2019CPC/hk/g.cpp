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
const int maxn = 100000 + 5;


int main() {
  int k;
  scanf("%d", &k);
  if (k == 1) {
    puts("2\n1\n2 1");
    return 0;
  }
  vector<int> fa, col, dp;
  function<int(int)> dfs = [&](int k) -> int {
    if (k == 1) {
      fa.push_back(-1); col.push_back(1); dp.push_back(1);
      return fa.size() - 1;
    } else if (k == 2) {
      col.push_back(1); col.push_back(1);
      dp.push_back(1); dp.push_back(1);
      fa.push_back(fa.size() + 1); fa.push_back(-1);
      return fa.size() - 1;
    } else {
      int v = dfs(k / 2);
      int sz = fa.size();
      fa[v] = sz + 2;
      col.push_back(1); col.push_back(1);
      dp.push_back(1); dp.push_back(1);
      fa.push_back(sz + 1); fa.push_back(sz + 2);
      fa.push_back(-1);
      dp.push_back(dp[v] + 1);
      if (k % 2 == 0) {
        col.push_back(dp.back() + 1);
      } else if (k % 2 == 1) {
        col.push_back(dp.back());
      }
      return sz + 2;
    }
  };
  dfs(k);
  int n = col.size();
  printf("%d\n", n);
  fa.pop_back();
  for (int i = 0; i + 1 < n; i++) {
    fa[i] = n - fa[i];
  }
  reverse(begin(fa), end(fa));
  for (int x: fa) printf("%d ", x);
  puts("");
  reverse(begin(col), end(col));
  for (int x: col) printf("%d ", x);
  return 0;
}