#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const ll mod = 1000000000 + 7;

ll n;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%lld", &n);
        if (n == 1){
            puts("3"); continue;
        }
        else if (n == 2){
            puts("9"); continue;
        }
        ll dp[2][3][3] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
        int tot = 0;
        for (ll i = 3; i <= n; i++, tot ^= 1){
            dp[tot ^ 1][0][0] = (dp[tot][0][1] + dp[tot][0][2]) % mod;
            dp[tot ^ 1][0][1] = (dp[tot][1][1] + dp[tot][1][2]) % mod;
            dp[tot ^ 1][0][2] = (dp[tot][2][1] + dp[tot][2][2]) % mod;
            dp[tot ^ 1][1][0] = (dp[tot][0][0] + dp[tot][0][1]) % mod;
            dp[tot ^ 1][2][0] = (dp[tot][0][0] + dp[tot][0][2]) % mod;
            dp[tot ^ 1][1][1] = (dp[tot][1][0] + dp[tot][1][2]) % mod;
            dp[tot ^ 1][1][2] = (dp[tot][2][0] + dp[tot][2][1] + dp[tot][2][2]) % mod;
            dp[tot ^ 1][2][1] = (dp[tot][1][0] + dp[tot][1][1] + dp[tot][1][2]) % mod;
            dp[tot ^ 1][2][2] = (dp[tot][2][0] + dp[tot][2][1]) % mod;
        }
        ll ans = 0;
        for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) ans += dp[tot][i][j], ans %= mod;
        printf("%lld\n", ans);
    }
    return 0;
}