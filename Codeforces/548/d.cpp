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
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int mu[maxn], vis[maxn], prime[maxn], tot;
void getMu() {
    mu[1] = 1;
    for (int i = 2; i < maxn; ++i) {
        if (!vis[i]) prime[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && i * prime[j] < maxn; ++j) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
            mu[i * prime[j]] = -mu[i];
        }
    }
}

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}
ll inv(ll x) {
    return qpow(x, mod - 2);
}

int m;
ll ans = 1;

int main() {
    getMu();
    cin >> m;
    ans = inv(m);
    for (int i = 2; i <= m; i++) {
        if (!mu[i]) continue;
        ll c = m / i, a = c * (2 * m - c) % mod, b = 1ll * m * (m - c);
        if (mu[i] > 0) ans -= a * inv(m) % mod * inv(m - c) % mod;
        else ans += a * inv(m) % mod * inv(m - c) % mod;
        ans += mod;
        ans %= mod;
    }
    cout << ans << endl;
    return 0;
}