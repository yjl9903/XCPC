#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 200000 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        x = x * x % mod; n >>= 1;
    }
    return r;
}
ll inv(ll x) { return qpow(x, mod - 2); }

ll wn[maxn << 2], rev[maxn << 2];
int init(int m) {
    int step = 0, n = 1;
    for (; n < m; n <<= 1) ++step;
    for (int i = 1; i < n; i++) 
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (step - 1));
    return n;  
}
void ntt(vector<ll>& a, int n, int op) {
    for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int h = 2; h <= n; h <<= 1) {
        ll wn = qpow(3, (mod - 1) / h);
        if (op == -1) wn = inv(wn);
        for (int i = 0; i < n; i += h) {
            ll w = 1;
            for (int j = i; j < i + h / 2; j++) {
                ll u = a[j], t = a[j + h / 2] * w % mod;
                a[j] = (u + t) % mod;
                a[j + h / 2] = (u - t + mod) % mod;
                w = w * wn % mod;
            }
        }
    }
    if (op == -1) {
        ll rn = inv(n);
        for (int i = 0; i < n; i++) a[i] = a[i] * rn % mod;
    }
}

int n, m;

int main() {
    scanf("%d%d", &n, &m);
    int lim = init(n + m + 1);
    for (int i = 0; i < lim; i++) cout << rev[i] << ' '; cout << endl;
    vector<ll> a(lim, 0), b(lim, 0);
    for (int i = 0; i <= n; i++) scanf("%lld", &a[i]);
    for (int i = 0; i <= m; i++) scanf("%lld", &b[i]);
    puts("??");
    ntt(a, lim, 1); 
    puts("??");
    ntt(b, lim, 1);
    // for (int i = 0; i < lim; i++) cout << a[i] << ' '; cout << endl;
    // for (int i = 0; i < lim; i++) cout << b[i] << ' '; cout << endl;
    // for (int i = 0; i < lim; i++) a[i] = a[i] * b[i] % mod;
    // ntt(a, lim, -1);
    // for (int i = 0; i <= n + m; i++) {
    //     if (i) putchar(' ');
    //     printf("%lld", a[i]);
    // }
    return 0;
}