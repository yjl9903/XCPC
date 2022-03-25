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

int n, a[maxn], pre[maxn], pos[maxn];

int dp[20][maxn];
void build() {
  for (int i = 1; i <= n + 1; i++) dp[0][i] = pre[i - 1];
  for (int j = 1; j < 20; j++)
    for (int i = 1; i + (1 << j) <= n + 2; i++)
      dp[j][i] = min(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
}
int qmin(int l, int r) {
  int k = __lg(r - l + 1);
  return min(dp[k][l], dp[k][r - (1 << k) + 1]);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    pre[i] = pre[i - 1] + a[i];
  }
  build();
  for (int i = -30; i <= 30; i++) pos[i] = -1;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int p = 1;
    // dbg(i);
    for (int mx = 30; mx >= -30; mx--) {
      int pos = ::pos[mx + 30];
      if (pos == -1) continue;
      if (pos >= p) {
        // dbg(p, mx, pos);
        // dbg(pre[i], qmin(p, pos));
        ans = max(ans, pre[i] - max(mx, a[i]) - qmin(p, pos));
        p = pos + 1;
      }
    }
    pos[a[i] + 30] = i;
  }
  printf("%d\n", ans);
  return 0;
}