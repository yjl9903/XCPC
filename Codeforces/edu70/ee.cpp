#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int inf = 1 << 20;
const int maxn = 100 + 5;

inline int add(int x, int y) {
    x += y;
    return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
    x -= y;
    return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
    return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
    int r = 1;
    while (n > 0) {
        if (n & 1) r = 1ll * r * x % mod;
        n >>= 1; x = 1ll * x * x % mod;
    }
    return r;
}
inline int inv(int x) {
    return qpow(x, mod - 2);
}

int n, G[maxn][maxn], dis[maxn][maxn];

int ans, dp[maxn];
bool vis[maxn];
void dfs(int u) {
    vis[u] = 1;
    dp[u] = 1;
    for (int i = 1; i <= n; i++) {
        if (!G[u][i]) continue;
        if (vis[i]) {
            dp[u] += dp[i]; continue;
        }
        if (dis[1][u] + G[u][i] == dis[1][i]) {

        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    while (cin >> n) {
        ans = 0;
        for (int i = 1; i <= n; i++) {
            string g; cin >> g;
            vis[i] = 1; dp[i] = 0;
            for (int j = 1; j <= n; j++) {
                G[i][j] = g[i] - '0';
                if (G[i][j]) dis[i][j] = G[i][j];
                else dis[i][j] = inf;
            }
        }
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                }
            }
        }
        dfs(1);

    }
    return 0;
}