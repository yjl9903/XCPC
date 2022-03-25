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

int n, m, k, a[maxn], mx[maxn][maxn], q[maxn];

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      a[j] = i * j / __gcd(i, j);
    }
    int l = 1, r = 0;
    for (int j = 1; j < k; j++) {
      while (l <= r && a[q[r]] <= a[j]) r--;
      q[++r] = j;
    }
    for (int j = k; j <= m; j++) {
      while (l <= r && a[q[r]] <= a[j]) r--;
      q[++r] = j;
      while (j - q[l] >= k) l++;
      mx[i][j] = a[q[l]];
    }
  }
  // for (int i = 1; i <= n; i++) {
  //   for (int j = k; j <= m; j++) {
  //     dbg(i, j, mx[i][j]);
  //   }
  // }
  ll ans = 0;
  for (int j = k; j <= m; j++) {
    int l = 1, r = 0;
    for (int i = 1; i < k; i++) {
      while (l <= r && mx[q[r]][j] <= mx[i][j]) r--;
      q[++r] = i;
    }
    for (int i = k; i <= n; i++) {
      while (l <= r && mx[q[r]][j] <= mx[i][j]) r--;
      q[++r] = i;
      while (i - q[l] >= k) l++;
      ans += mx[q[l]][j];
    }
  }
  cout << ans << endl;
  return 0;
}