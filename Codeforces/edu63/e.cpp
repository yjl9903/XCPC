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
const int mod = 1e6 + 3;
const int inf = 1 << 30;
const int maxn = 2000000 + 5;
const double eps = 1e-8;

int query(int x) {
    cout << "? " << x << endl;
    cin >> x; return x;
}

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

ll fac[maxn], a[20], inv[maxn];
struct Lagrange {
    ll cc[20]; int n;
    void build(int nn) {
        n = nn;
        for (int i = 1; i <= n; i++) {
            cc[i] = Inv(fac[i - 1] * fac[n - i]) * a[i] % mod;
            if ((n - i) % 2 == 1) cc[i] = (mod - cc[i]) % mod;
        }
    }
    ll get(ll x) {
        if (x <= n) return a[x];
        ll ans = 0, tmp = 1;
        for (int i = 1; i <= n; i++) tmp = tmp * (x - i) % mod;
        for (int i = 1; i <= n; i++) {
            ans += tmp * inv[x - i] % mod * cc[i] % mod;
            if (ans >= mod) ans -= mod;
        }
        return ans;
    }
} f;

int main() {
    fac[0] = 1; 
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod, inv[i] = Inv(i);
    for (int i = 0; i <= 15; i++) {
        a[i + 1] = query(i);
    }
    f.build(13);
    for (int i = 0; i < mod; i++) {
        if (!f.get(i + 1)) {
            cout << "! " << i << endl;
            return 0;
        }
    }
    cout << "! -1" << endl;
    return 0;
}