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
const int inf = 1 << 30;
const int maxn = 30 + 5;

int n, G[maxn][maxn], vis[maxn];

ll ans, tot;
vector<int> stk, stk2;
void dfs(int now, int cnt) {
    if (cnt == n) {
        ans = max(ans, tot);
        return ;
    }
    if (2 * n - now + 1 < n - cnt) return ;

    for (int i = 1; i <= 2 * n; i++) {
        if (i == now) continue;
        if (vis[i]) tot -= G[i][now];
        else tot += G[i][now];
    }
    vis[now] = 1;
    dfs(now + 1, cnt + 1);
    vis[now] = 0;
    for (int i = 1; i <= 2 * n; i++) {
        if (i == now) continue;
        if (vis[i]) tot += G[i][now];
        else tot -= G[i][now];
    }

    if (now != 1) dfs(now + 1, cnt);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= 2 * n; i++) {
        for (int j = 1; j <= 2 * n; j++) {
            scanf("%d,", &G[i][j]);
        }
    }
    dfs(1, 0);
    cout << ans << '\n';
    return 0;
}