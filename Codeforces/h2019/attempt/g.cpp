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

ll two[maxn], S[300][300];
int f[maxn], inv[maxn], finv[maxn];
void init(){
    S[0][0] = 1;
    for (int i = 1; i <= 200; i++) for (int j = 1; j <= 200; j++) S[i][j] = (S[i - 1][j - 1] + S[i - 1][j] * j % mod) % mod;
    inv[1] = 1;
    for (int i = 2; i < maxn; i++) inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
    f[0] = finv[0] = 1; 
    for (int i = 1; i < maxn; i++) {
        f[i] = f[i - 1] * 1ll * i % mod;
        finv[i] = finv[i - 1] * 1ll * inv[i] % mod;
    }
    two[0] = 1; for (int i = 1; i < maxn; i++) two[i] = 2ll * two[i - 1] % mod;
}
inline int C(int n, int m){
    if (m < 0 || m > n) return 0;
    return f[n] * 1ll * finv[n - m] % mod * finv[m] % mod;
}
inline void add(ll& x, ll y) {
    x += y; if (x >= mod) x -= mod;
}

vector<int> edge[maxn];
int n, k, siz[maxn];
vector<ll> dp[maxn];
ll ans[maxn];

vector<ll> mul(vector<ll>& x, vector<ll>& y, int k1, int k2) {
    k1 = min(k1, k); k2 = min(k2, k);
    vector<ll> ans(k + 1, 0);
    for (int i = 0; i <= k1; i++) {
        for (int j = 0; j <= k2; j++) {
            if (i + j > k) break;
            add(ans[i + j], x[i] * y[j] % mod);
        }
    }
    return ans;
}

void dfs(int u, int f) {
    siz[u] = 1;
    vector<ll> x(k + 1, 0); x[0] = 2; 
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs(v, u);
        vector<ll> y = vector<ll>(dp[v]);
        y[0] = two[siz[v]];
        y[1] = (y[1] + two[siz[v]] - 1 + mod) % mod;
        for (int i = 2; i <= k; i++) y[i] = (y[i] + dp[v][i - 1]) % mod;
        x = mul(x, y, siz[u], siz[v]);
        siz[u] += siz[v];
    }
    dp[u] = x;
    // dbg(u, x[1], x[2]);
    for (int& v: edge[u]) {
        if (v == f) continue;
        ll t = (two[n - siz[v]] - 1 + mod) % mod;
        add(ans[1], t * (two[siz[v]] - 1 + mod) % mod);
        for (int i = 1; i < k; i++) {
            // add(ans[i + 1], C(k, i) * t % mod * dp[v][i] * ::f[i] % mod);
            add(ans[i + 1], t * dp[v][i] % mod);
        }
        ll rs = two[siz[u] - siz[v]] % mod;
        x[1] = (x[1] - (two[siz[v]] - 1) * rs % mod + mod) % mod;
        for (int i = 2; i <= k; i++) {
            x[i] = (x[i] - dp[v][i - 1] * rs % mod + mod) % mod;
        }
        for (int i = 1; i <= k; i++) {
            x[i] = (x[i] - dp[v][i] * rs % mod + mod) % mod;
        }
    }
    // add(ans, x[k] * two[n - siz[u]] % mod * ::f[k] % mod);
    for (int i = 2; i <= k; i++) {
        add(ans[i], x[i] * two[n - siz[u]]  % mod);
    }
    // dbg(u, ans);
}

int main(){
    init();
    scanf("%d%d", &n, &k);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1, 0);
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= k; j++) cout << dp[i][j] << ' ';
    //     cout << endl;
    // }
    ll r = 0;
    for (int i = 0; i <= k; i++) {
        r = (r + S[k][i] * f[i] % mod * ans[i]) % mod;
    }
    cout << r << endl;
    return 0;
}