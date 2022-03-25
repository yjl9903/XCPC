#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;
const int mod = 1000000007;

int inv[maxn];
void init(){
    inv[1] = 1; inv[0] = 0;
    for (int i = 2; i < maxn; i++) inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
}

int n, m, p[1005];
ll dp[maxn];

int main(){
    init();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", p + i);
    p[0] = p[n + 1] = 0;

    ll res = 0;
    for (int i = 1; i <= n; i++){
        dp[i] = 1ll * p[i] * (100 - p[i - 1]) % mod * inv[10000] % mod;
        res = (res + dp[i] * (100 - p[i + 1]) % mod * inv[100] % mod) % mod;
    }
    for (int l = 2; l <= n; l++){
        ll f = 1;
        for (int k = 1; k <= m; k++) f = (f * l) % mod;
        for (int i = 1; i + l - 1 <= n; i++){
            dp[i] = dp[i] * p[i + l - 1] % mod * inv[100] % mod;
            res = (res + dp[i] * f % mod * (100 - p[i + l]) % mod * inv[100] % mod) % mod;
        }
    }
    printf("%lld\n", res);
    return 0;
}