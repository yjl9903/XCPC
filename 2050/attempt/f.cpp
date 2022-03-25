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
const int maxn = 10000 + 5;

int n, sc, a[maxn], b[maxn], c[maxn];
ll dp[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &sc);
        for (int i = 1; i <= n; i++) scanf("%d%d%d", a + i, b + i, c + i), dp[i] = -1;
        dp[0] = sc; int mx = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = mx - 1; j >= 0; j--) {
                ll tot = dp[j]; if (tot > b[i]) tot = b[i];
                if (tot > a[i]) {
                    dp[j + 1] = max(dp[j + 1], tot - a[i] + c[i]);
                }
                dp[j] += c[i];
            }
            ll tot = dp[mx]; if (tot > b[i]) tot = b[i];
            dp[mx] += c[i];
            if (tot > a[i]) {
                dp[++mx] = tot - a[i] + c[i];
            }
        }
        printf("%d\n", mx);
    }
    return 0;
}