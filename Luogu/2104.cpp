#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 500 + 5;

vector<int> edge[maxn];
int n, m, v[maxn];

int dp[maxn][maxn], siz[maxn];
void dfs(int u, int f) {
    siz[u] = 1; dp[u][1] = v[u];
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs(v, u);
        for (int i = siz[u]; i; i--) {
            for (int j = 0; j <= siz[v]; j++) {
                dp[u][i + j] = max(dp[u][i + j], dp[u][i] + dp[v][j]);
            }
        }
        siz[u] += siz[v];
    }
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1, x; i <= n; i++) {
        scanf("%d%d", &x, v + i);
        edge[x].push_back(i);
    }
    dfs(0, -1);
    cout << dp[0][m + 1] << endl;
    return 0;
}