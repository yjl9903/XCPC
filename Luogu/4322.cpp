#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 3000 + 5;

int k, n, s[maxn], p[maxn];
vector<int> edge[maxn];

int siz[maxn];
double dp[maxn][maxn];
int check(double x) {
    function<void(int,int)> dfs = [&](int u, int f) {
        siz[u] = 1; dp[u][0] = 0; dp[u][1] = p[u] - x * s[u];
        for (int i = 2; i <= k; i++) dp[u][i] = -1e9;
        for (int v: edge[u]) {
            if (v == f) continue;
            dfs(v, u);
            for (int i = siz[u]; i >= 1; i--) {
                for (int j = 0; j <= siz[v] && i + j <= k; j++) {
                    dp[u][i + j] = max(dp[u][i + j], dp[u][i] + dp[v][j]);
                }
            }
            siz[u] += siz[v];
        }
    };
    dfs(0, -1);
    return dp[0][k] >= 0;
}

int main() {
    scanf("%d%d", &k, &n); k++;
    for (int i = 1, f; i <= n; i++) {
        scanf("%d%d%d", s + i, p + i, &f);
        edge[f].push_back(i);
    }
    double l = 0.0, r = 10000.0;
    for (int T = 0; T < 100; T++) {
        double m = (l + r) / 2.0;
        if (check(m)) l = m;
        else r = m;
    }
    printf("%.3lf", l);
    return 0;
}