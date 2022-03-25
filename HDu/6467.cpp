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
const ll mod = 1000000007;
const int maxn = 100000 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1ll; x = x * x % mod;
    }
    return r;
}

ll n;

int main() {
    while (scanf("%lld", &n) == 1) {
        ll ans = (n - 1) % mod * qpow(2, n) + 1;
        printf("%lld\n", ans % mod);
    }
    return 0;
}