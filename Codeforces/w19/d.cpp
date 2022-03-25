#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int maxn = 200000 + 5;

ll qpow(ll x, ll n, ll mod = mod) {
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

int m, p[maxn], a[maxn];
ll pre[maxn], suf[maxn];
map<int,int> mp;

int main() {
    scanf("%d", &m);
    for (int i = 0; i < m; i++) scanf("%d", p + i), mp[p[i]]++;
    ll ap = 1, ans = 1; int cnt = 0;
    for (auto& x: mp) a[++cnt] = x.second + 1;
    pre[0] = 1;
    for (int i = 1; i <= cnt; i++) pre[i] = pre[i - 1] * a[i] % (mod - 1);
    suf[cnt + 1] = 1;
    for (int i = cnt; i >= 1; i--) suf[i] = suf[i + 1] * a[i] % (mod - 1);
    int i = 1;
    for (auto& x: mp) {
        ll tot = pre[i - 1] * suf[i + 1] % (mod - 1);
        for (int i = 1; i <= x.second; i++) {
            ans = ans * qpow(x.first, 1ll * i * tot % (mod - 1)) % mod;
        }
        i++;
    }
    cout << ans << endl;
    return 0;
}