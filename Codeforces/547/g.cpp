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
const int mod = 998244353;
const int maxn = 200000 + 5;

vector<PII> edge[maxn];
int n, k, deg[maxn];

int dp[maxn][2], cnt, res[maxn];
void dfs(int u, int f) {
    // u not good -> 0
    // u is good -> 1
    dp[u][0] = 0; dp[u][1] = 1;
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f) continue;
        dfs(v, u);
        dp[u][0] += max(dp[v][1], dp[v][0]);
        dp[u][1] += max(dp[v][1], dp[v][0]);
    }
    if ((int)edge[u].size() > cnt) dp[u][1]--;
}
int check(int x) {
    cnt = x;
    dfs(1, 0);
    return n - dp[1][0] <= k || n - dp[1][1] <= k; 
}

void solve(int u, int f, int c) {
    int i = 1;
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f) continue;
        if (i == c) i++;
        res[x.second] = i > cnt ? cnt : i;
        solve(v, u, i);
        i++;
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1, x, y; i < n; i++) {
        scanf("%d%d", &x, &y);
        edge[x].push_back({y, i});
        edge[y].push_back({x, i});
        deg[x]++; deg[y]++;
    }
    int lf = 0;
    for (int i = 1; i <= n; i++) if (deg[i] == 1) lf++;
    if (n - lf <= k) {
        puts("1"); for (int i = 1; i < n; i++) printf("1 ");
        return 0;
    }
    int l = 2, r = n - 1, ans = -1;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (check(m)) {
            ans = m; r = m - 1;
        } else {
            l = m + 1;
        }
    }
    cnt = ans;
    cout << ans << endl;
    solve(1, 0, 0);
    for (int i = 1; i < n; i++) printf("%d ", res[i]);
    return 0;
}