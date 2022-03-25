#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 300000 + 5;
const ll mod = (ll)1e9 + 7;

int n;
ll a[maxn], pre[maxn], pre2[maxn], pre3[maxn];

void add(ll& x, ll t){ x += t; x %= mod; }

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d", a + i);
        pre[i] = (pre[i - 1] + a[i]) % mod;
        pre2[i] = (pre2[i - 1] + 1ll * i * a[i] % mod) % mod;
    }
    for (int i = n; i > 0; i--) pre3[i] = (pre3[i + 1] + 1ll * (n - i + 1) * a[i] % mod) % mod;;
    ll ans = 0;
    for (int i = 1; i <= n; i++){
        ll w; scanf("%lld", &w);
        ll a1 = pre2[i - 1], a2 = pre3[n - i + 2], a3 = (pre[n - i + 1] - pre[i - 1] + mod) % mod * 1ll * i % mod;
        // cout << a1 << ' ' << a2 << ' ' << a3 << endl;
        add(ans, w * a1); add(ans, w * a2); add(ans, w * a3);
    }
    printf("%lld\n", ans);
    return 0;
}