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

int n, l[maxn], r[maxn];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", l + i);
    for (int i = 1; i <= n; i++) scanf("%d", r + i);
    ll sum = 1;
    ll ex = 1, dx = 1;
    for (int i = 1; i <= n; i++) sum = sum * (r[i] - l[i] + 1) % mod, dx = dx * inv(r[i] - l[i] + 1) % mod;
    for (int i = 1; i < n; i++) {
        int ll = max(l[i], l[i + 1]);
        int rr = min(r[i], r[i + 1]);
        if (ll > rr) continue;
        int len = rr - ll + 1;
        long long p1 = 1ll * len * inv(r[i] - l[i] + 1) % mod;
        long long p2 = 1ll * len * inv(r[i + 1] - l[i + 1] + 1) % mod;
        // long long p = p1 * p2 % mod;
        long long p = p1 * inv(r[i + 1] - l[i + 1] + 1) % mod;
        p = (1 - p + mod) % mod;
        ex = (ex + p) % mod;
        dx = (dx + p * ((1 - p + mod) % mod) % mod) % mod;
    }
    cout << ex << endl;
    cout << dx * sum % mod << endl;
    ll ans = (ex * ex % mod + dx * sum % mod) % mod;
    cout << ans;
    return 0;
}