#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 500000 + 5;

ll qpow(ll x, ll n = mod - 2) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}

int f[maxn], inv[maxn], finv[maxn];
void init(){
    inv[1] = 1;
    for (int i = 2; i < maxn; i++) inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
    f[0] = finv[0] = 1; 
    for (int i = 1; i < maxn; i++) {
        f[i] = f[i - 1] * 1ll * i % mod;
        finv[i] = finv[i - 1] * 1ll * inv[i] % mod;
    }
}
int C(int n, int m){
    if (m < 0 || m > n) return 0;
    return f[n] * 1ll * finv[n - m] % mod * finv[m] % mod;
}

int n, m;
ll a[maxn], b[maxn];

int main(){
    init();
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &m);
        if (m > n) {
            puts("0"); continue;
        }
        if (m == n) {
            printf("%lld\n", 1ll * f[n - 1] * inv[2] % mod); continue;
        }
        if (m == 0) {
            puts("1"); continue;
        }
        ll ans = 0;
        for (int i = 0; i <= n - m; i++) {
            ans = (ans + 1ll * C(n - m, i) * C(m + i - 1, m)) % mod;
        }
        printf("%lld\n", ans * f[n] % mod * finv[n - m] % mod * qpow(inv[2], n - m) % mod);
    }
    return 0;
}