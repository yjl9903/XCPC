#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 40000 + 5;

int head[maxn], to[maxn * 2], nxt[maxn * 2], d[maxn * 2], tot;
void add(int x, int y, int w){
    to[++tot] = y; nxt[tot] = head[x]; d[tot] = w; head[x] = tot;
}

int n, m;

int dp[maxn][20], dep[maxn], dis[maxn];
void dfs(int u, int fa){
    dp[u][0] = fa; dep[u] = dep[fa] + 1;
    for (int i = head[u]; i; i = nxt[i]){
        int v = to[i];
        if (v == fa) continue;
        dis[v] = dis[u] + d[i];
        dfs(v, u);
    }
}
void init(){
    ms(dp, 0); dep[0] = dis[0] = 0;
    dfs(1, 0); 
    for (int j = 1; j < 20; j++) 
        for (int i = 1; i <= n; i++) 
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
}
int lca(int x, int y){
    if (dep[x] < dep[y]) swap(x, y);
    int tmp = dep[x] - dep[y];
    for (int i = 0; tmp; i++, tmp >>= 1)
        if (tmp & 1) x = dp[x][i];
    if (x == y) return x;
    for (int i = 19; i >= 0; i--){
        if (dp[x][i] != dp[y][i]){
            x = dp[x][i]; y = dp[y][i];
        }
    }
    return dp[x][0];
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        ms(head, 0); tot = 0;
        scanf("%d%d", &n, &m);
        for (int i = 2; i <= n; i++){
            int x, y, d; scanf("%d%d%d", &x, &y, &d);
            add(x, y, d); add(y, x, d);
        }
        init();
        while (m--){
            int x, y; scanf("%d%d", &x, &y);
            printf("%d\n", dis[x] + dis[y] - 2 * dis[lca(x, y)]);
        }
    }
    return 0;
}