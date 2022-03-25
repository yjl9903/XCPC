#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 5000 + 5;

vector<int> edge[maxn];
int n, b, d[maxn], c[maxn];

// min cost of subtree-i buy j things, with discount or not
ll dp[maxn][maxn][2];
int siz[maxn];
void dfs(int u, int f) {
    siz[u] = 1;
    dp[u][0][0] = 0;
    dp[u][1][0] = c[u];
    dp[u][1][1] = c[u] - d[u];
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs(v, u);
        for (int i = siz[u]; i >= 0; i--) {
            for (int j = 1; j <= siz[v]; j++) {
                dp[u][i + j][0] = min(dp[u][i + j][0], dp[u][i][0] + dp[v][j][0]);
                dp[u][i + j][1] = min(dp[u][i + j][1], dp[u][i][1] + dp[v][j][0]);
                dp[u][i + j][1] = min(dp[u][i + j][1], dp[u][i][1] + dp[v][j][1]);
            }
        }
        siz[u] += siz[v];
    }
}

int main(){
    scanf("%d%d", &n, &b);
    for (int i = 1, x; i <= n; i++) {
        for (int j = 0; j <= n; j++) dp[i][j][0] = dp[i][j][1] = 1ll << 60;
        scanf("%d%d", c + i, d + i);
        if (i == 1) continue;
        scanf("%d", &x);
        edge[x].push_back(i);
    }
    dfs(1, 0);
    int ans = 0;
    for (int i = 1; i <= n; i++) if (min(dp[1][i][0], dp[1][i][1]) <= b) ans = i;
    cout << ans << endl;
    return 0;
}