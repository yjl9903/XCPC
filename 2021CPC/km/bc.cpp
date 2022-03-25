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
const int maxn = 100 + 5;

int n, a[maxn], b[maxn], f[maxn][maxn][maxn];

int dfs(int l, int r, int k) {
  if (l == r) return a[l] != k;
  if (f[l][r][k] != -1) return f[l][r][k];
  int ans = inf;
  for (int i = 1; i <= n; i++) {
    {
      int cur = dfs(l + 1, r, i);
      if (a[l] == k || a[l] == i) {
        ans = min(ans, cur + int(i != k));
      } else {
        ans = min(ans, cur + int(i != k) + 1);
      }
    }
    {
      int cur = dfs(l, r - 1, i);
      if (a[r] == k || a[r] == i) {
        ans = min(ans, cur + int(i != k));
      } else {
        ans = min(ans, cur + int(i != k) + 1);
      }
    }
  }
  return f[l][r][k] = ans;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    int m = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      if (m == 0) b[++m] = a[i];
      else if (a[i] != b[m]) b[++m] = a[i];
    }
    swap(a, b);
    n = m;
    ms(f, -1);
    int ans = dfs(1, n, 1);
    for (int i = 2; i <= n; i++) {
      ans = min(ans, dfs(1, n, i));
    }
    printf("%d\n", ans);
  }
  return 0;
}