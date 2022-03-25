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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 1000 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}
ll inv2 = qpow(2, mod - 2);

void fwt(int a[], int n, int op = 1) {
    for (int d = 1; d < n; d <<= 1)
        for (int i = 0, t = d << 1; i < n; i += t)
            for (int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j] = (1ll * x + 1ll * y) % mod;
                a[i + j + d] = (1ll * x + mod - 1ll * y) % mod;
                if (op != 1) {
                    // inv2 = 499122177
                    a[i + j] = 1ll * a[i + j] * inv2 % mod;
                    a[i + j + d] = 1ll * a[i + j + d] * inv2 % mod;
                }
            }
}

int n, m, v[maxn], dp[maxn][1 << 10], tmp[1 << 10], ans[1 << 10];
vector<int> edge[maxn];
void dfs(int u, int f) {
    dp[u][v[u]] = 1;
    for (int v: edge[u]) {
        if (v == f) continue;
        dfs(v, u);
        for (int i = 0; i < m; i++) tmp[i] = dp[u][i];
        fwt(tmp, m);
        fwt(dp[v], m);
        for (int i = 0; i < m; i++) tmp[i] = 1ll * tmp[i] * dp[v][i] % mod;
        fwt(tmp, m, -1);
        for (int i = 0; i < m; i++) dp[u][i] = (dp[u][i] + 1ll * tmp[i] % mod) % mod;
    }
    for (int i = 0; i < m; i++) ans[i] = (ans[i] + dp[u][i]) % mod;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        ms(dp, 0); ms(ans, 0);
        for (int i = 1; i <= n; i++) {
            edge[i].clear();
        }
        for (int i = 1; i <= n; i++) scanf("%d", v + i);
        for (int i = 2, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v); edge[v].push_back(u);
        }
        dfs(1, 0);
        for (int i = 0; i < m; i++) {
            if (i) putchar(' ');
            printf("%d", ans[i]);
        }
        puts("");
    }
    return 0;
}