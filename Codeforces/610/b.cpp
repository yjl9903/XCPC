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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, p, k, a[maxn];
ll dp[maxn], pre[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &p, &k);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      dp[i] = 0;
    }
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++) {
      pre[i] = pre[i - 1] + a[i];
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      dp[i] = a[i];
      if (i < k) {
        if (pre[i] <= p) ans = i;
      } else if (i >= k && i < k + k) {
        dp[i] += pre[i - k];
        if (dp[i] <= p) ans = i;
      } else {
        dp[i] += dp[i - k];
        if (dp[i] <= p) ans = i;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}