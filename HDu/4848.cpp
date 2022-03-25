#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 30 + 5;
const int inf = 1 << 30;

int G[maxn][maxn], t[maxn], vis[maxn], n;
int res;

void floyd(){
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
}

void dfs(int p, int d, int sum, int cnt){
    if (sum >= res) return;
    if (d > t[p]) return;
    if (cnt == n){
        res = min(res, sum);
        return;
    }
    for (int i = 2; i <= n; i++) if (!vis[i]){
        if (d + G[p][i] > t[i]) return;
    }
    // cout << p << ' ' << d  << ' ' << sum << endl;
    for (int i = 1; i <= n; i++) if (G[p][i] && !vis[i]){
        if (d > t[i]) return;
        vis[i] = 1;
        if (sum + (n - cnt) * (d + G[p][i]) <= res)
            dfs(i, d + G[p][i], sum + d + G[p][i], cnt + 1);
        vis[i] = 0;
    }
}

int main(){
    while (cin >> n && n){
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> G[i][j];
        floyd(); res = 1 << 30; ms(vis, 0);
        for (int i = 2; i <= n; i++) cin >> t[i];
        vis[1] = 1; dfs(1, 0, 0, 1);
        if (res == inf) res = -1;
        cout << res << endl;
    }
    return 0;
}