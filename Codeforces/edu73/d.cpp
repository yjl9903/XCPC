#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
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
const ll inf = 1ll << 60;
const int maxn = 300000 + 5;

int n, a[maxn], b[maxn];
ll dp[maxn][3];

void gmin(ll& x, ll y) {
    if (y < x) x = y;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", a + i, b + i);
        }
        dp[1][1] = b[1]; dp[1][2] = 2ll * b[1];
        for (int i = 2; i <= n; i++) {
            dp[i][0] = dp[i][1] = dp[i][2] = inf;
            if (a[i] != a[i - 1]) {
                gmin(dp[i][0], dp[i - 1][0]);
                gmin(dp[i][1], dp[i - 1][1] + b[i]);
                gmin(dp[i][2], dp[i - 1][2] + 2ll * b[i]);
            }
            if (a[i] != a[i - 1] + 1) {
                gmin(dp[i][0], dp[i - 1][1]);
                gmin(dp[i][1], dp[i - 1][2] + b[i]);
            }
            if (a[i] != a[i - 1] + 2) {
                gmin(dp[i][0], dp[i - 1][2]);
            }
            if (a[i] + 1 != a[i - 1]) {
                gmin(dp[i][1], dp[i - 1][0] + b[i]);
                gmin(dp[i][2], dp[i - 1][1] + 2ll * b[i]);
            }
            if (a[i] + 2 != a[i - 1]) {
                gmin(dp[i][2], dp[i - 1][0] + 2ll * b[i]);
            }
            dbg(dp[i][0], dp[i][1], dp[i][2]);
        }
        printf("%lld\n", min(dp[n][2], min(dp[n][0], dp[n][1])));
    }
    return 0;
}