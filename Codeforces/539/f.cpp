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
const int mod = 1e9 + 7;
const int maxn = 1000000 + 5;

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
ll T(ll n, ll k) {
    if (k == n) return 1;
    return k * qpow(n, n - k - 1) % mod;
}

int n, m, a, b;

int main() {
    init();
    cin >> n >> m >> a >> b;
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ll tot = 1ll * C(m - 1, i - 1) * C(n - 2, i - 1) % mod * f[i - 1] % mod * qpow(m, n - i - 1) % mod * T(n, i + 1) % mod;
        ans += tot; if (ans >= mod) ans -= mod;
    }
    cout << ans << endl;
    return 0;
}