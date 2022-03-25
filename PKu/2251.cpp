#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 35;

int map[maxn][maxn][maxn], vis[maxn][maxn][maxn], d[maxn][maxn][maxn], L, R, C, res, ex, ey, ez, sx, sy, sz;
int dir[6][3] = {{1, 0, 0}, {0, 1, 0}, {-1, 0, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};

int bfs(){
    queue<int> Qx, Qy, Qz;
    Qx.push(sx);    Qy.push(sy);    Qz.push(sz);
    vis[sx][sy][sz] = 1;    d[sx][sy][sz] = 0;
    int x, y, z, tx, ty, tz;
    while (!Qx.empty()){
        x = Qx.front(); y = Qy.front(); z = Qz.front();
        Qx.pop();   Qy.pop();   Qz.pop();
        for (int i = 0; i < 6; i++){
            tx = x + dir[i][0]; ty = y + dir[i][1]; tz = z + dir[i][2];
            if (tx >= 0 && ty >= 0 && tz >= 0 && tx < L && ty < R && tz < C && !vis[tx][ty][tz] && map[tx][ty][tz]){
                vis[tx][ty][tz] = 1;
                d[tx][ty][tz] = d[x][y][z] + 1;
                if (tx == ex && ty == ey && tz == ez)
                    return d[tx][ty][tz];
                Qx.push(tx);    Qy.push(ty);    Qz.push(tz);
            }
        }
    }
    return -1;
}

int main(){
    while (cin >> L >> R >> C && L && R && C){
        memset(vis, 0, sizeof vis);
        char x;
        for (int i = 0; i < L; i++)
            for (int j = 0; j < R; j++)
                for (int k = 0; k < C; k++){
                    cin >> x;
                    if (x == 'S')
                        map[i][j][k] = 2, sx = i, sy = j, sz = k;
                    else if (x == '.')
                        map[i][j][k] = 1;
                    else if (x == '#')
                        map[i][j][k] = 0;
                    else if (x == 'E')
                        map[i][j][k] = 3, ex = i, ey = j, ez = k;
                }
        
        res = bfs();
        //dfs(sx, sy, sz, 0);
        if (res != -1)
            cout << "Escaped in " << res << " minute(s)." << endl;
        else
            cout << "Trapped!" << endl;
    }
    return 0;
}