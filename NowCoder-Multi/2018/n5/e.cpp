#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;
const int inf = 1 << 30;

int G[maxn][maxn] = {0}, visx[maxn], visy[maxn], nxt[maxn], wx[maxn] = {0}, wy[maxn] = {0}, d;
int n, a[maxn][4], vis[4 * maxn] = {0};

int dfs(int p){
    visx[p] = 1;
    for (int i = 0; i < n; i++) {
        if (visy[i]) continue;
        int t = wx[p] + wy[i] - G[p][i];
        if (t == 0){
            visy[i] = 1;
            if (nxt[i] == -1 || dfs(nxt[i])){
                nxt[i] = p;
                return true;
            }
        }
        else if (t > 0) {
            d = min(d, t);
        }
    }
    return false;
}
int km(){
    ms(nxt, -1); 
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) wx[i] = max(wx[i], G[i][j]);
    for (int i = 0; i < n; i++){
        while (1){
            ms(visx, 0); ms(visy, 0); d = inf;
            if (dfs(i)) break;
            for (int i = 0; i < n; i++) {
                if (visx[i]) wx[i] -= d;
                if (visy[i]) wy[i] += d;
            }
        }
    }
    int res = 0;
    for (int i = 0; i < n; i++) res += G[nxt[i]][i];
    return 4 * n - res;
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d%d%d%d", &a[i][0], &a[i][1], &a[i][2], &a[i][3]);
    for (int i = 0, x, b, c, d; i < n; i++){
        scanf("%d%d%d%d", &x, &b, &c, &d);
        vis[x] = vis[b] = vis[c] = vis[d] = 1;
        for (int j = 0; j < n; j++) for (int k = 0; k < 4; k++) if (vis[a[j][k]]) G[i][j]++;
        vis[x] = vis[b] = vis[c] = vis[d] = 0;
    }
    printf("%d\n", km());
    return 0;
}