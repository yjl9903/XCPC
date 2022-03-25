#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const ll mod = 998244353;

ll n, q, a[maxn];

ll qpow(ll m){
    ll r = 1, a = 2;
    while (m > 0){
        if (m & 1) r = (r * a) % mod;
        m >>= 1;
        a = a * a % mod;
    }
    return r % mod;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%lld%lld", &n, &q); a[0] = 0;
        for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
        for (int i = 1; i <= n; i++) a[i] = (a[i] + a[i - 1]) % mod;
        int cmd, x, y;
        ll t = qpow(n * q);
        while (q--){
            scanf("%d%d%d", &cmd, &x, &y);
            if (cmd == 2){
                printf("%lld\n", t * ((a[y] - a[x - 1] + mod) % mod) % mod);
            }
        }
    }
    return 0;
}