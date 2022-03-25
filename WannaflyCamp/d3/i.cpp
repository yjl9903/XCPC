#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 200000 + 5;

ll qpow(ll x, ll n = mod - 2) {
    ll r = 1;
    while (n) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}

int n, q, pre[maxn], siz[maxn], val[maxn];

int find(int x) { return x == pre[x] ? x : find(pre[x]); }

int main(){
    scanf("%d%d", &n, &q);
    int sum = 1; for (int i = 1; i <= n; i++) sum = 1ll * sum * 3 % mod;
    for (int i = 1; i <= n; i++) pre[i] = i, siz[i] = 1, val[i] = 1;
    ll k1 = qpow(3), k2 = qpow(2);
    int op, x, y;
    while (q--) {
        scanf("%d%d", &op, &x);
        if (op == 1) {
            scanf("%d", &y);
            x = find(x); y = find(y);
            if (siz[y] < siz[x]) {
                val[y] = 1ll * val[y] * qpow(val[x]) % mod * k2 % mod;
                val[x] = 2ll * val[x] % mod * k1 % mod;
                pre[y] = x; siz[x] += siz[y];
            } else {
                val[x] = 2ll * val[x] % mod * qpow(val[y]) % mod;
                val[y] = 1ll * val[y] * k1 % mod;
                pre[x] = y; siz[y] += siz[x];
            }
        } else if (op == 2) {
            int ans = sum;
            while (x != pre[x]) {
                ans = 1ll * ans * val[x] % mod;
                x = pre[x];
            }
            printf("%d\n", 1ll * ans * val[x] % mod);
        }
    }
    return 0;
}