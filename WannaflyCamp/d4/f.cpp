#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100 + 5;

int map[maxn][maxn];

int dir[8][2] = {
    -2, -1,
    -2, 1,
    -1, -2, 
    -1, 2,
    1, -2,
    1, 2,
    2, -1,
    2, 1
};

int n, m, sx, sy, vis[maxn][maxn];
void dfs(int x, int y) {
    for (int i = 0; i < 8; i++) {
        int tx = x + dir[i][0];
        int ty = y + dir[i][1];
        if (tx < 1 || ty < 1 || tx > n || ty > m || vis[tx][ty]) continue;
        vis[tx][ty] = 1;
        dfs(tx, ty);
    }
}   

int main(){
    cin >> n >> m >> sx >> sy;
    vis[sx][sy] = 1;
    dfs(sx, sy); 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << vis[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}