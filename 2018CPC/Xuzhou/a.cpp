#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const int mod = 1000000000 + 7;

int n, k;

int a[maxn], ans = 0;
void dfs(int p){
    if (p == n){
        int flag = 1;
        for (int i = 0; i < n; i++) {
            // printf("%d ", a[i] + a[(i + 1) % n]);
            if (a[i] + a[(i + 1) % n] == (1 << k) - 1){
                flag = 0; break;
            }
        }
        // puts("");
        if (flag) ans++;
        return;
    }
    for (int i = 0; i < (1 << k); i++){
        a[p] = i;
        dfs(p + 1);
    }
}

ll qpow(ll x, ll n){
    ll r = 1;
    while (n){
        if (n & 1) r = (r * x) % mod;
        n >>= 1;
        x = (x * x) % mod;
    }
    return r % mod;
}

ll f(ll n, ll m){
    if (n == 0) return m;
    return m * qpow(m - 1, n - 1) - f(n - 1, m);
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &k);
        // ans = 0; dfs(0);
        ll a = qpow(2, k), b = a * (a - 1) % mod, c = a;
        if (k == 1){
            puts("2"); continue;
        }
        if (n == 1){
            printf("%lld\n", a); continue;
        }
        else if (n == 2){
            printf("%lld\n", b); continue;
        }

        for (int i = 3; i <= n; i++){
            // a = (c * qpow(c - 1, i - 1) % mod + mod - a) % mod;
            // printf("%lld\n", a);
            ll t = b;
            b = (a + (qpow(c - 1, i - 1) - qpow(c - 1, i - 2) + mod) % mod * c % mod) % mod;
            a = t;
        }
        printf("%lld\n", b);
    }
    return 0;
}