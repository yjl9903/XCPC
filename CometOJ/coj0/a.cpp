#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cstdlib>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

ll Prime[11] = {2, 3, 5, 7, 13, 17, 19, 23} ;

inline ll expow(ll a, ll b, ll p){
    ll res = 1 ;
    while (b){
        if (b & 1) 
            (res *= a) %= p ;
        (a *= a) %= p, b >>= 1 ; 
    }
    return res % p ;
}
inline bool Test(ll p, ll x){
    ll r = 0, d = x - 1 ;
    while (!(d & 1)) d >>= 1, ++ r ;
    for (ll i = expow(p, d, x), j ; r ; -- r){
        j = i * i % x ;
        if (j == 1){
            if (i == 1 || i == x - 1) 
                return 1 ; 
            return 0 ;
        }
        i = j ;
    }
    return 0 ;
}
inline bool Miller_Rabin(ll x){
    if (x == 1) return 0 ;
    for (int i = 0 ; i < 8 ; ++ i){
        if (x == Prime[i]) return 1 ;
        if (!(x % Prime[i])) return 0 ;
        if (!Test(Prime[i], x)) return 0 ;
    }
    return 1 ;
}
ll res[maxn], tot ;
inline int pksrand(){
    return rand() << 15 ^ rand() ;
}
inline ll Irand(ll x){
    return (((ll)pksrand()) << 30 ^ pksrand()) % x ; //2
}
inline ll guisuMul(ll a, ll b, ll x){
    return (a * b - (ll) ((long double) a * b / x + 1e-9) * x) % x;
} 
inline ll qwq(ll x){
    ll A = Irand(x), C = Irand(x) ;
    ll t1 = A, t2 = (guisuMul(A, A, x) + C) % x ; // 1
    ll dif = max(t1, t2) - min(t1, t2), G = __gcd(x, dif) ;
    while (G == 1){
        t1 = (guisuMul(t1, t1, x) + C) % x ;
        t2 = (guisuMul(t2, t2, x) + C) % x ;
        t2 = (guisuMul(t2, t2, x) + C) % x ;
        dif = max(t1, t2) - min(t1, t2), G = __gcd(x, dif) ;
    }
    return G ;
}
inline void Pollard_Rho(ll x){
    if (x == 1) return ;
    if (Miller_Rabin(x)) {
        res[++tot] = x; return ;
    }
    ll y = x ; while (y == x) y = qwq(x) ;
    Pollard_Rho(y), Pollard_Rho(x / y) ;
}

ll qpow(ll x, int n) {
    ll r = 1;
    while (n) {
        if (n & 1) r = r * x;
        n >>= 1; x = x * x;
    }
    return r;
}

int n;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        int sq = (int)sqrt(1.0 * n);
        if (sq * sq == n) {
            puts("infty"); continue;
        }
        if (n % 4) {
            puts("0 0"); continue;
        }
        tot = 0; n /= 4; ll m = n;
        Pollard_Rho(n);
        ll ans = 1; int cnt = 1;
        for (int i = 1; i <= tot; i++) {
            int c = 0;
            while (n % res[i] == 0) n /= res[i], c++;
            cnt *= c + 1;
            ll x = (qpow(res[i], c + 1) - 1) / (res[i] - 1); x %= mod;
            ans = ans * x % mod;
        }
        printf("%d %lld\n", cnt / 2, ans * m % mod);
    }
    return 0;
}