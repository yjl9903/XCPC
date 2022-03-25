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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}
void add(ll& x, ll y) {
    x += y; if (x >= mod) x -= mod;
}

int n;
ll g[maxn], f[maxn], pre[maxn];

int main() {
    g[1] = 45;
    for (int i = 2; i < maxn; i++) {
        ll x = qpow(10, i);
        g[i] = x * (x - 1) / 2; g[i] %= mod;
    }
    f[1] = g[1]; f[2] = g[2];
    pre[1] = f[1]; pre[2] = 10 * f[1] + f[2];
    for (int i = 3; i < maxn; i++) {
        f[i] = g[i];
        add(f[i], 20ll * pre[i - 2] % mod);
        pre[i] = f[i];
        add(pre[i], 10ll * pre[i - 1] % mod);
    }
    // for (int i = 1; i <= 5; i++) cout << g[i] << endl;
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        printf("%I64d\n", f[n]);
    }
    return 0;
}