#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn = 100005;
const ll mod = 1000000007;
 
int k, q, a[maxn];
ll dp[maxn][2], sum[maxn];
 
int main(){
    while (~scanf("%d%d", &q, &k)){
    dp[0][1] = 1; dp[0][0] = 0;
    for (int i = 1; i < maxn; i++){
        if (i >= k) dp[i][0] = dp[i - k][1];
        dp[i][1] = (dp[i - 1][0] + dp[i - 1][1]) % mod;
    }
    sum[0] = 0;
    for (int i = 1; i < maxn; i++){
        // printf("%lld\n", sum[i]);
        sum[i] = ((sum[i - 1] + dp[i][0]) % mod + dp[i][1]) % mod;
    }
    while (q--){
        int l, r;
        scanf("%d%d", &l, &r);
        ll ans = (sum[r] + mod - sum[l - 1]) % mod;
        printf("%lld\n", ans);
    }}
    return 0;
}