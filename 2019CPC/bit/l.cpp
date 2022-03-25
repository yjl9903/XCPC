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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

ll inv[maxn];
ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}

int n, m;
vector<int> edge[maxn];

ll dp[maxn];
ll dfs(int u) {
    if (dp[u]) return dp[u];
    ll ans = 1 + inv[(int)edge[u].size() + 1];
    for (int& v: edge[u]) {
        ans += inv[(int)edge[u].size()] * (dfs(v) + 1) % mod;
        ans %= mod;
    }
    // dbg(u, ans);
    return dp[u] = ans;
}

int main() {
    for (int i = 1; i < maxn; i++) inv[i] = qpow(i, mod - 2);
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            edge[i].clear(); dp[i] = 0;
        }
        for (int i = 1, u, v; i <= m; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
        }
        printf("%lld\n", dfs(1));
    }
    return 0;
}