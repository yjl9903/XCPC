#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const ll inf = 1e10;
const int maxn = 1000 + 5;

int n, m, s, k, c;
ll G[maxn][maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        vector<int> key;
        scanf("%d%d%d%d%d", &n, &m, &s, &k, &c);
        for (int i = 1, x; i <= k; i++) scanf("%d", &x), key.push_back(x);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) G[i][j] = inf;
            G[i][i] = 0;
        }
        for (int i = 1, u, v, w; i <= m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            G[u][v] = min(G[u][v], 1ll * w);
            G[v][u] = G[u][v];
        }
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
                }
            }
        }
        ll hero = 0, mx = 0;
        for (int i = 1; i <= n; i++) hero = max(hero, G[s][i]);
        for (int i = 1; i <= n; i++) {
            ll mn = inf;
            for (int x: key) {
                mn = min(mn, G[x][i]);
            }
            mx = max(mx, mn);
        }
        if (hero <= 1ll * c * mx) printf("%lld\n", hero);
        else printf("%lld\n", mx);
    }
    return 0;
}