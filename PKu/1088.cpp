#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

int r, c, map[maxn][maxn], dp[maxn][maxn], vis[maxn][maxn] = {0};
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int dfs(int x, int y){
    if (dp[x][y] != -1) return dp[x][y]; 
    dp[x][y] = 1;
    for (int i = 0; i < 4; i++){
        int tx = x + dir[i][0], ty = y + dir[i][1];
        if (tx < 0 || ty < 0 || tx >= r || ty >= c) continue;
        if (map[tx][ty] >= map[x][y]) continue;
        if (vis[tx][ty]) continue;
        dp[x][y] = max(dp[x][y], dfs(tx, ty) + 1);
    }
    return dp[x][y];
}

int main(){
    scanf("%d%d", &r, &c);
    for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) scanf("%d", &map[i][j]);
    int res = 0; ms(dp, -1); 
    for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) res = max(res, dfs(i, j));
    printf("%d\n", res);
    return 0;
}