#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
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
const int maxn = 150000 + 5;
const int maxm = 300 + 5;

int n, m, d, a[maxn], b[maxn], t[maxn];
ll dp[2][maxn];
int dq[maxn];

int main() {
  scanf("%d%d%d", &n, &m, &d);
  for (int i = 1; i <= m; i++) scanf("%d%d%d", a + i, b + i, t + i);
  int f = 0;
  for (int j = 1; j <= n; j++) dp[0][j] = b[1] - abs(a[1] - j);
  for (int i = 2; i <= m; i++, f ^= 1) {
    int l = 1, r = 0, tot = 0;
    ll dis = 1ll * d * (t[i] - t[i - 1]);
    for (int j = 1; j <= n; j++) {
      while (l <= r && dq[l] < j - dis) l++;
      while (tot < n && tot < j + dis) {
        tot++;
        while (l <= r && dp[f][dq[r]] <= dp[f][tot]) r--;
        dq[++r] = tot;
      }
      dp[f ^ 1][j] = b[i] - abs(a[i] - j);
      if (l <= r) dp[f ^ 1][j] += dp[f][dq[l]];
    }
  }
  ll ans = -inf;
  for (int i = 1; i <= n; i++) ans = max(ans, dp[f][i]);
  cout << ans;
  return 0;
}