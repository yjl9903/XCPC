#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1010;
const int inf = 1 << 30;

int G[maxn][maxn], T, N, dis[maxn], vis[maxn];

int dijkstra()
{
    
    for (int i = 1; i <= N; i++)
    {
        if (G[1][i] < dis[i])
            dis[i] = G[1][i];
    }
    vis[1] = 1; dis[1] = 0;

    for (int i = 1; i <= N; i++)
    {
        int min = inf, k = 1;
        for (int j = 1; j <= N; j++)
            if (!vis[j] && dis[j] < min)
                min = dis[j], k = j;
        vis[k] = 1;
        for (int j = 1; j <= N; j++)
            if (!vis[j] && min + G[k][j] < dis[j])
                dis[j] = min + G[k][j];
    }

    return dis[N];
}

int main(){
    while (cin >> T >> N){
        for (int i = 0; i < maxn; i++)
            for (int j = 0; j < maxn; j++)
                if (i != j)
                    G[i][j] = inf;
                else
                    G[i][j] = 0;
        fill(dis, dis + maxn, inf);
        fill(vis, vis + maxn, 0);
        int x, y, l, c;
        // cin >> T >> N;
        for (int i = 0; i < T; i++){
            cin >> x >> y >> l >> c;
            if (l * c < G[x][y])
                G[x][y] = G[y][x] = l * c; 
        }

        cout << dijkstra() << endl;
    }
    
    return 0;
}