#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 20000000 + 5;

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
ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}

int n;

int main(){
    init();
    cin >> n;
    ll ans = (qpow(2, n) - 1 + mod) % mod;
    for (int i = n - 1, f = 1; i >= 2; i--, f = -f) {
        ll k = (n - i) * (n - i - 1) / 2;
        k = (C(k, 2) - 1 + mod) % mod;
        ans = (ans + f * (C(n, i) * qpow(2, k) % mod) + mod) % mod;
    }
    cout << ans << endl;
    return 0;
}