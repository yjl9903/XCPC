#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}
ll inv(ll x) { return qpow(x, mod - 2); }
inline void add(ll& x, ll y) {
    x += y; if (x >= mod) x -= mod;
}

int n, x, a[205];
ll dp[205][maxn];

int main() {
    scanf("%d%d", &n, &x);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    sort(a, a + n); dp[n][x] = 1;
    for (int i = n - 1; i >= 0; i--) {
        ll iv = inv(i + 1);
        for (int j = 0; j <= x; j++) {
            add(dp[i][j % a[i]], dp[i + 1][j] * iv % mod);
            add(dp[i][j], (dp[i + 1][j] - dp[i + 1][j] * iv % mod + mod) % mod);
        }
    }
    ll ans = 0, f = 1;
    for (int i = 1; i <= n; i++) f = f * i % mod;
    for (int i = 0; i <= x; i++) add(ans, i * dp[0][i] % mod);
    cout << ans * f % mod << endl;
    return 0;
}