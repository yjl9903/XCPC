#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 500 + 5;
const int inf = 1 << 30;

int G[maxn][maxn], n, m, e;

bool visx[maxn], visy[maxn], vis[maxn];
int wx[maxn], wy[maxn], nxt[maxn], d;
int dfs(int p){
    visx[p] = 1;
    for (int i = 0; i < m; i++){
        if (visy[i] || G[p][i] == -1) continue;
        int t = wx[p] + wy[i] - G[p][i];
        if (t == 0){
            visy[i] = 1;
            if (nxt[i] == -1 || dfs(nxt[i])){
                nxt[i] = p;
                return true;
            }
        }
        else if (t >= 0){
            d = min(t, d);
        }
    }
    return false;
}
int km(){
    ms(nxt, -1); ms(wy, 0);
    for (int i = 0; i < n; i++) wx[i] = -inf;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) wx[i] = max(wx[i], G[i][j]);
    for (int i = 0; i < n; i++){
        while (true){
            ms(visx, 0); ms(visy, 0); d = inf;
            if (dfs(i)) break;
            if (d == inf) return -1;
            for (int i = 0; i < n; i++) if (visx[i]) wx[i] -= d;
            for (int i = 0; i < m; i++) if (visy[i]) wy[i] += d;
        }
    }
    int ans = 0;
    ms(vis, 0);
    for (int i = 0; i < m; i++) if (nxt[i] != -1) vis[nxt[i]] = 1, ans += G[nxt[i]][i];
    for (int i = 0; i < n; i++) if (!vis[i]) return -1;
    return ans;
}

int main(){
    int kase = 0;
    while (~scanf("%d%d%d", &n, &m, &e)){
        ms(G, -1);
        while (e--){
            int x, y, c; scanf("%d%d%d", &x, &y, &c);
            if (c >= 0) G[x][y] = c;
        }
        printf("Case %d: %d\n", ++kase, km());
    }
    return 0;
}