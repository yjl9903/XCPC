#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20 + 5;

int G[maxn][maxn], vis[maxn], n, maxd, open[maxn], cnt = 0;

bool dfs2(int p, int r){
    for (int i = 1; i <= n; i++){
        if (i == p || i == r) continue;
        if (G[p][i] && !open[i]){
            if (!vis[i]){
                vis[i] = 1;
                if (dfs2(i, p)) return true;
            }
            else
                return true;
        }
    }
    return false;
}

bool check(){
    for (int i = 1; i <= n; i++){
        if (open[i]) continue;
        int s = 0;
        for (int j = 1; j <= n; j++){
            if (G[i][j] && !open[j]) 
                s++;
        }
        if (s > 2) return false;
    }
    // cout << endl; for (int i = 1; i <= n; cout << open[i++] << ' '); cout << endl;
    // cout << endl << '+' << endl;
    ms(vis, 0); cnt = 0;
    for (int i = 1; i <= n; i++){
        if (!open[i] && !vis[i]){
            vis[i] = 1;
            if (dfs2(i, i)) return false;
            cnt++;
        }
        // cout << '-' << endl;
    }
    return maxd >= cnt - 1;
}

bool dfs(int p, int d){
    if (d == maxd){
        return check();
    }
    if (p > n) return false;

    open[p] = 1; if (dfs(p + 1, d + 1)) return true;
    open[p] = 0; if (dfs(p + 1, d)) return true;

    return false;
}

int main(){
    int kase = 0;
    while (cin >> n && n){
        int x, y; ms(G, 0);
        while (cin >> x >> y){
            if (x == -1 && y == -1) break;
            G[x][y] = G[y][x] = 1;
        }
        int flag = 0;
        for (maxd = 0; !flag; maxd++){
            ms(open, 0);
            flag = dfs(1, 0);
        }
        cout << "Set " << ++kase << ": Minimum links to open is ";
        cout << maxd - 1 << endl;
    }
    return 0;
}