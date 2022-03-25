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
const int maxn = 1000 + 5;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int pcd[maxn][maxn];
void add(int& x, int y) {
    x += y; if (x >= mod) x -= mod;
}
void add(ll& x, ll y) {
    x += y; if (x >= mod) x -= mod;
}
ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}

int n, m;
vector<PII> edge[maxn];

int deg[maxn], rt;
int dp[maxn][maxn];
void dfs(int u, int f) {
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f) continue;
        dfs(v, u);
        int f = 0;
        for (int i = 1; i <= m; i++) add(f, dp[v][i]);
        dbg(u, v, f);
        for (int i = 1; i <= m; i++) {
            if (i < x.second || i % x.second) dp[u][i] = 1ll * dp[u][i] * f % mod;
            else if (i == x.second) {
                int g = 0;
                for (int j = x.second; j <= m; j += x.second) add(g, dp[v][j]);
                dbg(g);
                dp[u][i] = 1ll * (f - g + mod) % mod * dp[u][i] % mod;
            } else {
                int g = 0;
                for (int j = x.second; j <= m; j += x.second) {
                    if (pcd[i][j] == x.second) add(g, dp[v][j]);
                }
                dp[u][i] = 1ll * (f - g + mod) % mod * dp[u][i] % mod;
            }
        }
        // for (int i = 1; i <= m; i++) {
        //     for (int j = 1; j <= m; j++) {
        //         if (gcd(i, j) != x.second) {
        //             dp[u][i] += dp[v][j];
        //             dp[u][i] %= mod;
        //         }
        //     }
        // }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) for (int j = 1; j <= m; j++) pcd[i][j] = gcd(i, j);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) dp[i][j] = 1;
    for (int i = 2, u, v, w; i <= n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        edge[u].push_back({v, w});
        edge[v].push_back({u, w});
        deg[u]++; deg[v]++;
    }
    dfs(1, 0);
    ll ans = 0;
    for (int i = 1; i <= m; i++) {
        ans += dp[1][i];
        ans %= mod;
    }
    cout << ans << endl;
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= m; j++) {
    //         cout << dp[i][j] << ' ';
    //     }
    //     puts("");
    // }
    return 0;
}