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
const int maxn = 3000 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}
ll inv(ll x) { return qpow(x, mod - 2); }

int n, q, a[maxn];
ll f[maxn][maxn];

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (a[i] > a[j]) f[i][j] = 1;
    ll inv2 = inv(2);
    for (int i = 1, x, y; i <= q; i++) {
        scanf("%d%d", &x, &y);
        f[x][y] = f[y][x] = (f[x][y] + f[y][x]) * inv2 % mod;
        for (int j = 1; j <= n; j++) if (j != x && j != y) {
            f[x][j] = f[y][j] = (f[x][j] + f[y][j]) * inv2 % mod;
            f[j][x] = f[j][y] = (f[j][x] + f[j][y]) * inv2 % mod;
        }
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) {
        ans += f[i][j]; if (ans >= mod) ans -= mod;
    }
    cout << ans * qpow(2, q) % mod << endl;
    return 0;
}