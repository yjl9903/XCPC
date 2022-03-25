#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 500 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}

int n, m, k, p, q;
ll dp[2][maxn][maxn];

void add(ll& x, ll y) {
    x += y; if (x >= mod) x -= mod;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        ms(dp, 0);
        scanf("%d%d%d%d%d", &n, &m, &k, &p, &q);
        int f = 0; dp[f][0][0] = 1;
        for (int i = 1; i < m; i++, f ^= 1) {
            ms(dp[f ^ 1], 0);
            for (int x = 0; x < n; x++) {
                for (int y = 0; x + y + 1 <= min(n - 1, i + 1); y++) {
                    add(dp[f ^ 1][x + 1][max(y - 1, 0)], dp[f][x][y] * p % mod);
                    add(dp[f ^ 1][max(x - 1, 0)][y + 1], dp[f][x][y] * q % mod);
                    add(dp[f ^ 1][x][y], dp[f][x][y] * (100 - p - q) % mod);
                }
            }
        }
        ll ans = 0, sum = 0;
        for (int x = 0; x < n; x++) {
            for (int y = 0; x + y + 1 <= min(n - 1, m); y++) {
                add(ans, qpow(x + y + 1, k) * dp[f][x][y] % mod);
                add(sum, dp[f][x][y]);
            }
        }
        ll pr = (qpow(100, m - 1) - sum + mod) % mod;
        // dbg(sum, pr);
        add(ans, pr * qpow(n, k) % mod);
        printf("%lld\n", ans);
    }
    return 0;
}