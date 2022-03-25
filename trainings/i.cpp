#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, q;

int head[maxn], to[maxn * 2], nxt[maxn * 2], tot;
void add(int x, int y){
    to[++tot] = y; nxt[tot] = head[x]; head[x] = tot;
}

int dp[maxn][20], dep[maxn];
void dfs(int u, int fa){
    dp[u][0] = fa; dep[u] = dep[fa] + 1;
    for (int i = head[u]; i; i = nxt[i]){
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);
    }
}
void init(){
    ms(dp, 0); dep[0] = 0;
    dfs(n + 1, 0); 
    for (int j = 1; j < 20; j++) 
        for (int i = 1; i <= n + 1; i++) 
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
    scanf("%d%d", &n, &q);
    for (int i = 1, f; i <= n; i++){
        scanf("%d", &f);
        if (f == -1) f = n + 1;
        else f++;
        add(f, i);
    }
    init();
    while (q--){
        int x, y; scanf("%d%d", &x, &y);
        x++; y++;
        int u = lca(x, y);
        // printf("%d %d %d\n",x, y, u);
        if (u == y) puts("Yes");
        else puts("No"); 
    }
    return 0;
}