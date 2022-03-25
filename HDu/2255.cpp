#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 300 + 5;
const int inf = 1 << 30;

int n, G[maxn][maxn];

bool visx[maxn], visy[maxn];
int nxt[maxn], wx[maxn], wy[maxn], d;
int dfs(int p){
    visx[p] = 1;
    for (int i = 0; i < n; i++){
        if (visy[i]) continue;
        int t = wx[p] + wy[i] - G[p][i];
        if (t == 0){
            visy[i] = 1;
            if (nxt[i] == -1 || dfs(nxt[i])){
                nxt[i] = p;
                return true;
            }
        }
        else if (t > 0){
            d = min(t, d);
        }
    }
    return false;
}
int km(){
    ms(nxt, -1); ms(wy, 0); ms(wx, 0);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++){
        wx[i] = max(wx[i], G[i][j]);
    }
    for (int i = 0; i < n; i++){
        while (true){
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
    return res;
}

int main(){
    while (~scanf("%d", &n)){
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) scanf("%d", &G[i][j]);
        printf("%d\n", km());
    }
    return 0;
}