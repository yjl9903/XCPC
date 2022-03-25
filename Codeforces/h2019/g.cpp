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

ll two[maxn];
int f[maxn], inv[maxn], finv[maxn];
void init(){
    inv[1] = 1;
    for (int i = 2; i < maxn; i++) inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
    f[0] = finv[0] = 1; 
    for (int i = 1; i < maxn; i++) {
        f[i] = f[i - 1] * 1ll * i % mod;
        finv[i] = finv[i - 1] * 1ll * inv[i] % mod;
    }
    two[0] = 1; for (int i = 1; i < maxn; i++) two[i] = 2ll * two[i - 1] % mod;
}
int C(int n, int m){
    if (m < 0 || m > n) return 0;
    return f[n] * 1ll * finv[n - m] % mod * finv[m] % mod;
}
void add(ll& x, ll y) {
    x += y; if (x >= mod) x -= mod;
}

vector<int> edge[maxn];
int n, k, siz[maxn];
vector<ll> dp[maxn];
ll ans;

vector<ll> mul(vector<ll>& x, vector<ll>& y, int k1 = k, int k2 = k) {
    k1 = min(k1, k); k2 = min(k2, k);
    vector<ll> ans(k + 1, 0);
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= k; j++) {
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
        siz[u] += siz[v];

    }
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
    cout << ans << endl;
    return 0;
}