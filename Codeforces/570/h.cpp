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
const int maxn = 200 + 5;

int n, last[30]; ll k, dp[maxn][maxn];
char s[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> k >> s + 1;
    dp[0][0] = dp[1][0] = dp[1][1] = 1; 
    last[s[1] - 'a'] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i][0] = 1;
        int r = last[s[i] - 'a'];
        for (int j = 1; j <= i; j++) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
            if (r) {
                dp[i][j] -= dp[r - 1][j - 1];
            }
        }
        last[s[i] - 'a'] = i;
    }
    ll ans = 0;
    for (int i = n; i >= 0; i--) {
        dbg(i, dp[n][i]);
        ll tot = min(k, dp[n][i]);
        ans += tot * (n - i);
        k -= tot;
        if (k == 0) break;
    }
    if (k) puts("-1");
    else cout << ans << endl;
    return 0;
}