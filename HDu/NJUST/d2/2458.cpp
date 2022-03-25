#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200 + 5;

int G[maxn][maxn], g, b, m, cnt[2][maxn];

int nxt[maxn], vis[maxn];
int dfs(int p){
    for (int i = 1; i <= b; i++){
        if (!vis[i] && !G[p][i]){
            vis[i] = 1;
            if (nxt[i] == -1 || dfs(nxt[i])){
                nxt[i] = p;
                return 1;
            }
        }
    }
    return 0;
}
int match(){
    ms(nxt, -1); ms(cnt, 0);
    int ans = 0;
    for (int i = 1; i <= g; i++){
        ms(vis, 0); if (dfs(i)) ans++;
    }
    return b + g - ans;
}

int main(){
    int kase = 0;
    while (~scanf("%d%d%d", &g, &b, &m)){
        if (!g && !b && !m) break;
        ms(G, 0);
        while (m--){
            int x, y; scanf("%d%d", &x, &y);
            G[x][y] = 1;
        }
        printf("Case %d: %d\n", ++kase, match());
    }
    return 0;
}