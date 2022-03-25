#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

vector<int> edge[maxn];
int n, f[maxn], d[maxn];
ll dp[maxn][2];

void dfs(int u, int fa) {
    dp[u][0] = 0; dp[u][1] = f[u];
    for (int& v: edge[u]) {
        if (v == fa) continue;
        dfs(v, u);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += max(dp[v][0], dp[v][1] - d[min(u, v)]);
    }
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", f + i);
    for (int i = 1; i <= n; i++) scanf("%d", d + i);
    for (int i = 2; i <= n; i++) {
        if (i % 2) {
            if (3 * i + 1 > n) continue;
            edge[i].push_back(3 * i + 1);
            edge[3 * i + 1].push_back(i);
        } else {
            edge[i].push_back(i / 2);
            edge[i / 2].push_back(i);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!dp[i][1]) {
            dfs(i, 0); 
            ans += max(dp[i][0], dp[i][1]);
        }
    }
    cout << ans << endl;
    return 0;
} 