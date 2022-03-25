#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 6000 + 5;

int inv[maxn] = {0ll, 1ll}, f[maxn] = {1ll, 1ll}, dp[maxn][maxn];
int n, k;

int main(){
    for (int i = 2; i < maxn; i++) inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod, f[i] = 1ll * i * f[i - 1] % mod;
    for (int i = 1; i < maxn; i++) dp[i][1] = (dp[i - 1][1] + 1ll * i * (i - 1) * inv[4] % mod) % mod;
    for (int h = 2; h < maxn; h++) {
        for (int i = 1; i < maxn; i++) {
            dp[i][h] = (dp[i - 1][h] + 2ll * dp[i - 1][h - 1] % mod * inv[i] % mod) % mod;
        }
    }
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &k);
        ll ans = dp[n][k] - dp[n - 1][k] + mod;
        printf("Case #%d: %lld\n", ++kase, ans * f[n] % mod);
    }
    return 0;
}