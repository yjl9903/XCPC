#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 998244353;
const int maxn = 100 + 5;

vector<PII> edge[maxn];
int n, q, dp[maxn][maxn];

void dfs(int u, int f) {
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f) continue;
        dfs(v, u);
        for (int i = q; i >= 1; i--) {
            for (int j = 0; j + 1 <= i; j++) {
                dp[u][i] = max(dp[u][i], dp[u][j] + dp[v][i - j - 1] + x.second);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 2, u, v, w; i <= n; i++) {
        scanf("%d%d%d", &u, &v, &w); 
        edge[u].push_back({v, w});
        edge[v].push_back({u, w});
    }
    dfs(1, 0);
    cout << dp[1][q] << endl;
    return 0;
}