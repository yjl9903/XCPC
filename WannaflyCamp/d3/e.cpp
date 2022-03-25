#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

vector<int> edge[maxn];
int n, m, k[maxn];

int dp[maxn][2];
void dfs(int u, int f) {
    int s1 = 0, s2 = 1;
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs(v, u);
        s1 += max(dp[v][0], dp[v][1]);
        s2 += dp[v][0];
    }
    dp[u][0] = s1; dp[u][1] = s2;
}

int dp2[maxn][2];// greedy, rebuild greedy
void dfs2(int u, int f, int k1, int k2) {
    int s1 = max(k1, k2), s2 = k1 + 1;
    for (int& v: edge[u]) {
        if (v == f) continue;
        s1 += max(dp[v][0], dp[v][1]);
        s2 += dp[v][0];
    }
    dp2[u][0] = s1; dp2[u][1] = s2;
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs2(v, u, s1 - max(dp[v][0], dp[v][1]), s2 - dp[v][0]);
    }
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for (int i = 1; i <= m; i++) scanf("%d", k + i);
    dfs(1, 0); 
    dfs2(1, 0, 0, 0);
    int ans = max(dp[1][0], dp[1][1]), last = 0; // 0: not choose
    if (dp[1][1] > dp[1][0]) last = 1;
    printf("%d\n", ans);
    for (int i = 1; i <= m; i++) {
        ans = 1ll * ans * n % mod;
        if (last == 0) {
            ans = (ans + max(dp2[k[i]][0], dp2[k[i]][1])) % mod;
            if (dp2[k[i]][1] > dp2[k[i]][0]) last = 1;
        } else last = 0;
        printf("%d\n", ans);
    }
    return 0;
}