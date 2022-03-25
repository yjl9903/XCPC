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

int n, m, a[maxn][maxn];
map<int,int> cnt[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n + m; i++) cnt[i].clear();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        scanf("%d", &a[i][j]);
        if (i + j < (n + m - 1) / 2) {
          // dbg(i, j, i + j);
          cnt[i + j][a[i][j]]++;
        } else {
          // dbg(i, j, n - 1 - i + m - 1 - j);
          cnt[n - 1 - i + m - 1 - j][a[i][j]]++;
        }
      }
    }
    int ans = 0, M = (n + m) / 2;
    if ((n + m) % 2 == 0) {
      M--;
    }
    for (int k = 0; k < M; k++) {
      int sum = 0, mx = 0;
      for (auto x: cnt[k]) {
        mx = max(mx, x.second);
        sum += x.second;
      }
      ans += sum - mx;
    }
    printf("%d\n", ans);
  }
  return 0;
}