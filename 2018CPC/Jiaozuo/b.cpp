#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const ll inf = 1ll << 60;

int n, m, k, a[maxn];
ll dp[2][maxn][6];
char f[5];

ll cal(ll a, ll b, int n){
    if (f[n] == '+') return a + b;
    if (f[n] == '-') return a - b;
    if (f[n] == '*') return a * b;
    if (f[n] == '/') return a / b;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        scanf("%s", f);
        // ms(dp, 0);
        for (int i = 0; i <= n; i++) for (int j = 0; j < 6; j++) dp[0][i][j] = -inf;
        for (int i = 0; i <= n; i++) for (int j = 0; j < 6; j++) dp[1][i][j] = inf;
        dp[0][0][0] = dp[1][0][0] = k;
        ll ans = -inf;
        for (int i = 1; i <= n; i++){
            dp[0][i][0] = dp[1][i][0] = k;
            for (int j = 0; j < m; j++) {
                dp[0][i][j + 1] = dp[0][i - 1][j + 1];
                dp[1][i][j + 1] = dp[1][i - 1][j + 1];
                if (dp[0][i - 1][j] == -inf) break;
                
                dp[0][i][j + 1] = max(dp[0][i][j + 1], cal(dp[0][i - 1][j], a[i], j));
                // if (dp[1][i - 1][j] != inf)
                dp[0][i][j + 1] = max(dp[0][i][j + 1], cal(dp[1][i - 1][j], a[i], j));

                dp[1][i][j + 1] = min(dp[1][i][j + 1], cal(dp[0][i - 1][j], a[i], j));
                // if (dp[1][i - 1][j] != -inf)
                dp[1][i][j + 1] = min(dp[1][i][j + 1], cal(dp[1][i - 1][j], a[i], j));
            }
            // dp[i][1] = cal(dp[i - 1][0], a[i], 0);
            // dp[i][2] = cal(dp[i - 1][1], a[i], 1);
            ans = max(ans, dp[0][i][m]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}