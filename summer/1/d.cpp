#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200 + 5;

int n, a[maxn], b[maxn];
ll dp[maxn][maxn];

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        ll ans = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", a + i), ans += a[i];
        for (int i = 1; i <= n; i++) {
            scanf("%d", b + i);
            for (int j = i; j <= n; j++) dp[i][j] = 1e18;
        }
        b[0] = b[n + 1] = 0;
        for (int len = 1; len <= n; len++) {
            for (int l = 1; l + len - 1 <= n; l++) {
                int r = l + len - 1;
                for (int j = l; j <= r; j++) {
                    dp[l][r] = min(dp[l][r], dp[l][j - 1] + dp[j + 1][r] + b[l - 1] + b[r + 1]);
                }
            }
        }
        printf("Case #%d: %lld\n", ++kase, ans + dp[1][n]);
    }
    return 0;
}