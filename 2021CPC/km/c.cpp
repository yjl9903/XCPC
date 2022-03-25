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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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

int n, a[maxn], b[maxn], f[maxn][maxn][2];
vector<int> bag[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    int m = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      if (m == 0) b[++m] = a[i];
      else if (a[i] != b[m]) b[++m] = a[i];
      bag[i].clear();
    }
    swap(a, b);
    n = m;
    for (int i = 1; i <= n; i++) {
      bag[a[i]].push_back(i);
      for (int j = 1; j <= n; j++) {
        f[i][j][0] = f[i][j][1] = 0;
      }
    }
    for (int len = 2; len <= n; len++) {
      for (int l = 1; l + len - 1 <= n; l++) {
        int r = l + len - 1;
        f[l][r][0] = f[l][r][1] = inf;
        for (int p: bag[a[l]]) {
          if (p < l) continue;
          if (p >= r) break;
          int cur = min(f[l][p][0], f[l][p][1]);
          int val = f[p + 1][r][0] + 1;
          if (a[l] == a[r]) {
            val = min(val, f[p + 1][r][1]);
          } else {
            val = min(val, f[p + 1][r][1] + 1);
          }
          val += cur;
          f[l][r][0] = min(f[l][r][0], val);
        }
        for (int p: bag[a[r]]) {
          if (p <= l) continue;
          if (p > r) break;
          int cur = min(f[p][r][0], f[p][r][1]);
          int val = f[l][p - 1][1] + 1;
          if (a[l] == a[r]) {
            val = min(val, f[l][p - 1][0]);
          } else {
            val = min(val, f[l][p - 1][0] + 1);
          }
          val += cur;
          f[l][r][1] = min(f[l][r][1], val);
        }
        if (a[l] == a[r]) {
          int cur = 1 + min(f[l + 1][r - 1][0], f[l + 1][r - 1][1]);
          f[l][r][0] = min(f[l][r][0], cur);
          f[l][r][1] = min(f[l][r][1], cur);
        }
      }
    }
    // dfs(1, n, 0);
    // for (int i = 1; i <= n; i++) {
    //   for (int j = i; j <= n; j++) {
    //     dbg(i, j, dfs(i, j, 0), dfs(i, j, 1));
    //   }
    // }
    printf("%d\n", min(f[1][n][0], f[1][n][1]));
  }
  return 0;
}