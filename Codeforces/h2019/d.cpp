#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n) {
        if (n & 1) r = 1ll * r * x % mod;
        n >>= 1; x = 1ll * x * x % mod;
    }
    return r % mod;
}
ll inv(ll x) { return qpow(x, mod - 2); }

ll n, k;

ll f[100][50000];
ll dp(ll p, int a, int k) {
    if (f[a][k] > -1) return f[a][k];
    if (k == 0) return qpow(p, a);
    ll ans = 0;
    for (int i = 0; i <= a; i++) ans = (ans + dp(p, i, k - 1)) % mod;
    // dbg(a, k, ans, inv(a + 1));
    return f[a][k] = ans * inv(a + 1) % mod;
}
ll cal(ll p, int a) {
    for (int i = 0; i <= a; i++) for (int j = 0; j <= k; j++) f[i][j] = -1;
    return dp(p, a, k);
}

int main(){
    cin >> n >> k;
    ll ans = 1;
    for (ll i = 2; 1ll * i * i <= n; i++) {
        if (n % i) continue;
        int cnt = 0;
        while (n % i == 0) cnt++, n /= i;
        ll x = cal(i, cnt);
        ans = ans * x % mod;
        // dbg(x);
        // ans = ans * cal(i, cnt) % mod;
        // dbg(i, cnt, cal(i, cnt));
    }
    if (n > 1) ans = ans * cal(n, 1) % mod;
    // dbg(n, cal(n, 1));
    cout << ans;
    return 0;
}