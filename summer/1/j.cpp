#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 400 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}
void add(ll& x, ll y) {
    x += y; if (x >= mod) x -= mod;
}
// void add(int& x, int y)  {
//     x += y; if (x >= mod) x -= mod;
// }
int f[maxn], inv[maxn], finv[maxn];
void init(){
    inv[1] = 1;
    for (int i = 2; i < maxn; i++) inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
    f[0] = finv[0] = 1; 
    for (int i = 1; i < maxn; i++) {
        f[i] = f[i - 1] * 1ll * i % mod;
        finv[i] = finv[i - 1] * 1ll * inv[i] % mod;
    }
}
int C(int n, int m){
    if (m < 0 || m > n) return 0;
    return f[n] * 1ll * finv[n - m] % mod * finv[m] % mod;
}

int n, siz[maxn];
vector<int> edge[maxn];

ll dp[maxn][maxn];
void dfs(int u, int ff) {
    siz[u] = 1;
    dp[u][1] = 1; // ?
    for (int& v: edge[u]) {
        if (v == ff) continue;

        dfs(v, u);
        vector<ll> tmp(siz[u] + siz[v] + 1, 0);
        ll sum = f[siz[v]];
        for (int i = 0; i <= siz[v]; i++) {
            add(sum, mod - dp[v][i]);
            for (int j = 1; j <= siz[u]; j++) {
                add(tmp[i + j], sum * dp[u][j] % mod * C(i + j - 1, i) % mod * C(siz[u] + siz[v] - i - j, siz[v] - i) % mod);
            }
        }

        siz[u] += siz[v];
        for (int i = 1; i <= siz[u]; i++) dp[u][i] = tmp[i];
    }
}

int main() {
    init();
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 2, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        printf("Case #%d: ", ++kase);
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            ms(dp, 0);
            dfs(i, 0);
            for (int j = 1; j <= n; j++) add(ans, dp[i][j]);
        }
        printf("%lld\n", ans);
        for (int i = 1; i <= n; i++) edge[i].clear();
    }
    return 0;
}