#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const int mod = 998244353;

int a, b, c, d, n;

ll qpow(int m){
    ll r = 1, a = 2;
    while (m > 0){
        if (m & 1) r = (r * a) % mod;
        m >>= 1;
        a = (a * a) % mod;
    }
    return r % mod;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d%d%d", &a, &b, &c, &d);
        ll ans = qpow(a), ans1 = 0;
        // ll ans1 = (qpow(b) + qpow(c) + (b + d) * 1ll * qpow(c) % mod - b + mod) % mod;
        if (b) ans1 = (ans1 + qpow(b)) % mod;
        if (c) ans1 = (ans1 + qpow(c)) % mod;
        ans1 = (ans1  + (b + d) * 1ll * qpow(c) % mod - b + mod) % mod;
        if (b > 0 && c > 0) ans1 = (ans1 - 1 + mod) % mod;
        printf("%lld\n", ans1 * ans % mod);
    }
    return 0;
}