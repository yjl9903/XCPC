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
const int maxn = 200000 + 5;

int n, k, dp[maxn][3];
char s[maxn], rgb[] = "RGB";

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%s", &n, &k, s);
        auto check = [&](int i, int tp) -> int {
            return (int)(s[i] != rgb[tp]);
        };
        auto gmin = [&](int& x, int y) {
            if (x > y) x = y;
        };
        int ans = inf;
        dp[0][0] = dp[0][1] = dp[0][2] = 0;
        for (int i = 0; i < k; i++) {
            dp[0][0] += check(i, i % 3);
            dp[0][1] += check(i, (i + 1) % 3);
            dp[0][2] += check(i, (i + 2) % 3);
        }
        // RGBRGB...
        // GBRGB...
        // BRGB...
        gmin(ans, dp[0][0]); gmin(ans, dp[0][1]); gmin(ans, dp[0][2]);
        for (int i = 1; i + k - 1 < n; i++) {
            dp[i][0] = dp[i - 1][2] - check(i - 1, 2) + check(i + k - 1, (k + 2) % 3);
            dp[i][1] = dp[i - 1][0] - check(i - 1, 0) + check(i + k - 1, k % 3);
            dp[i][2] = dp[i - 1][1] - check(i - 1, 1) + check(i + k - 1, (k + 1) % 3);
            gmin(ans, dp[i][0]); gmin(ans, dp[i][1]); gmin(ans, dp[i][2]);
        }
        printf("%d\n", ans);
    }
    return 0;
}