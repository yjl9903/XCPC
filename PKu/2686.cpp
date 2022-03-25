#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 30 + 5;
const double inf = 1e30;

int n, m, p, a, b, t[maxn], G[maxn][maxn];
double res = inf, dp[1 << 10][maxn];

int main(){
    while (~scanf("%d%d%d%d%d", &n, &m, &p, &a, &b)){
        if (!n && !m && !p && !a && !b) break;
        for (int i = 0; i < n; i++) scanf("%d", &t[i]);
        sort(t, t + n);
        ms(G, 0); res = inf;
        for (int i = 0; i < p; i++){
            int x, y, z; scanf("%d%d%d", &x, &y, &z);
            G[x][y] = G[y][x] = z;
        }
        int ss = (1 << n) - 1;
        for (int s = 0; s <= ss; s++){ fill(dp[s], dp[s] + maxn, -inf); dp[s][a] = 0;}
        for (int s = 0; s <= ss; s++){
            for (int i = 1; i <= m; i++) if (dp[s][i] >= 0){
                for (int v = 0; v < n; v++){
                    if (s & (1 << v)) continue;
                    for (int j = 1; j <= m; j++) if (i != j && G[i][j]){
                        if (dp[s | (1 << v)][j] <= 0 || dp[s | (1 << v)][j] > dp[s][i] + double(G[i][j]) / double(t[v]))
                            dp[s | (1 << v)][j] = dp[s][i] + double(G[i][j]) / double(t[v]);
                    }
                }
            }
            if (dp[s][b] >= 0) res = min(dp[s][b], res);
        }
        if (res >= inf) printf("Impossible\n");
        else printf("%.3f\n", res);
    }
    return 0;
}