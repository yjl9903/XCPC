#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 300000 + 5;
const int mod = 998244353;

int f[maxn], inv[maxn], finv[maxn];
void init(){
    inv[1] = 1;
    for (int i = 2; i < maxn; i++) inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
    f[0] = finv[0] = 1;
    for (int i = 1; i < maxn; i++) f[i] = f[i - 1] * 1ll * i % mod, finv[i] = finv[i - 1] * 1ll * inv[i] % mod;
}
int C(int n, int m){
    if (m < 0 || m > n) return 0;
    return f[n] * 1ll * finv[n - m] % mod * 1ll * finv[m] % mod;
}

int n, m, k;

int main(){
    init();
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d%d", &n, &m, &k);
        if (n == 1){
            if (k == 0) puts("1");
            else puts("0");
            continue;
        }
        if (m == 1){
            if (n <= k) puts("0");
            else puts("1");
            continue;
        }
        if (k < n){
            printf("%d\n", C(m + k - 1, k));
            continue;
        }
        if (1ll * (n - 1) * m < 1ll * k){
            puts("0");
            continue;
        }
        ll ans = C(m + k - 1, k);
        ll g = C(m, k / n) * 1ll * C(m + k % n - 1, k % n) % mod;
        for (ll i = k / n - 1, j = n; i >= 1; i--, j += n){
            g = (C(m, i) * 1ll * C(m + k % n + j - 1, k % n + j) % mod + mod - g) % mod;
        }
        printf("%lld\n", (ans + mod - g) % mod);
    }
    return 0;
}