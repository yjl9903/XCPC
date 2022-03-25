#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;
const ll mod = 998244353;

inline void add(ll& x, ll y) {
    x += y % mod; if (x >= mod) x-= mod;
}
inline ll qpow(ll x, ll n) {
    ll r = 1; 
    while (n) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r % mod;
}
inline ll inv(ll x) { return qpow(x, mod - 2); }

ll tree[maxn];
inline int lowbit(int x) {return x & -x;}
void update(int i) {
    while (i < maxn) tree[i]++, i += lowbit(i);
}
ll qsum(int i) {
    ll r = 0;
    while (i > 0) r += tree[i], i -= lowbit(i);
    return r;
}

int n, a[maxn], pre[maxn], vis[maxn];

int main(){
    scanf("%d", &n); 
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        if (a[i] > 0) vis[a[i]] = 1;
    }
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + 1 - vis[i];
    ll ans = 1ll * pre[n] * (pre[n] - 1) % mod * inv(4) % mod;
    ll fm = inv(pre[n]), c = 0;
    for (int i = n; i >= 1; i--) {
        if (a[i] != -1) {
            add(ans, qsum(a[i]));
            update(a[i]);
            add(ans, c * fm % mod * pre[a[i]] % mod);
            add(ans, (pre[n] - c) * fm % mod * (pre[n] - pre[a[i]]) % mod);
        } else {
            c++;
        }
    }
    cout << ans;
    return 0;
}