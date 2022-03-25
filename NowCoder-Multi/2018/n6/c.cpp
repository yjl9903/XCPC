#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;
const int mod = 998244353;

int f[maxn], inv[maxn], finv[maxn]; 
void init(){
    inv[1] = 1;
    for (int i = 2; i < maxn; i++) inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
    f[0] = finv[0] = 1;
    for (int i = 1; i < maxn; i++) f[i] = f[i - 1] * i % mod, finv[i] = 1ll * finv[i - 1] * inv[i] % mod;
}
ll C(ll n, ll m){
    if (m < 0 || m > n) return 0;
    return f[n] * 1ll * finv[n - m] % mod * finv[m] % mod;
}
ll A(ll n, ll m){
    if (m < 0 || m > n) return 0;
    return f[n] * 1ll * finv[n - m] % mod;
}

int main(){
    init();
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        ll n, m, res = 0; scanf("%lld%lld", &n, &m);
        // for (ll i = 1; i <= min(m, n); i++){
        //     res = (res + 1ll * A(m, i) * C(n - 1, i - 1) % mod) % mod;
        //     // printf("%lld %lld\n", A(m, i), C(n - 1, i - 1));
        // }
        ll c1 = m % mod, c2 = 1, fac= 1;
        for (ll i = 1; i <= min(n ,m); i++){
            fac = fac * i % mod;
            res = (res + fac * c1 % mod * c2) % mod;
            c1 = c1 * 1ll * ((m - i) % mod) % mod * inv[i + 1] % mod;
            c2 = c2 * 1ll * ((n - i) % mod) % mod * inv[i] % mod;
        }
        printf("Case #%d: %lld\n", ++kase, res);
    }
    return 0;
}