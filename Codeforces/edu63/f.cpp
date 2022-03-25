#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <random>
#include <ctime>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 2000000 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}
ll Inv(ll x) {
    return qpow(x, mod - 2);
}

ll fac[maxn], a[maxn], inv[maxn];
struct Lagrange {
    ll cc[maxn]; int n;
    // start on 1
    void build(int nn) {
        n = nn;
        for (int i = 1; i <= n; i++) {
            cc[i] = Inv(fac[i - 1] * fac[n - i] % mod) * a[i] % mod;
            if ((n - i) % 2 == 1) cc[i] = (mod - cc[i]) % mod;
        }
    }
    ll get(ll x) {
        if (x <= n) return a[x];
        ll ans = 0, tmp = 1;
        for (int i = 1; i <= n; i++) tmp = tmp * (x - i) % mod;
        for (int i = 1; i <= n; i++) {
            ans += tmp * Inv(x - i) % mod * cc[i] % mod;
            if (ans >= mod) ans -= mod;
        }
        return ans;
    }
} f;

int main() {
    fac[0] = 1; 
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ll n, k; cin >> n >> k;
    for (int i = 2; i <= k + 3; i++) {
        a[i] = (qpow(i - 1, k) + a[i - 1]) % mod;
    }
    f.build(k + 2);
    cout << f.get(n + 1) << endl;
    return 0;
}