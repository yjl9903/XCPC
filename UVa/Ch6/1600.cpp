#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
const int maxn = 20 + 5;

int map[maxn][maxn], vis[maxn][maxn], obs[maxn][maxn], m, n, k;
int dir[4][2] = {1, 0, 0, 1, -1, 0, 0, -1};
struct node{
    int x, y, d, stop;
};

int bfs(){
    memset(vis, 0, sizeof vis);     memset(obs, 0, sizeof obs);
    queue<node> q;
    node x = {1, 1, 0, 0};
    q.push(x);  vis[1][1] = 1;
    while (!q.empty()){
        x = q.front();  q.pop();
        //cout << x.x << ' ' << x.y << ' ' << x.d << endl;
        if (x.x == m && x.y == n)   return x.d;
        node t;
        for (int i = 0; i < 4; i++){
            t.x = x.x + dir[i][0];  t.y = x.y + dir[i][1];  t.d = x.d + 1;  t.stop = x.stop;
            if (t.x > 0 && t.y > 0 && t.x <= m && t.y <= n){
                if (!vis[t.x][t.y]){
                    if (map[t.x][t.y] == 0){
                        t.stop = 0;
                        q.push(t);
                        vis[t.x][t.y] = 1;
                    }
                    else if (t.stop < k){
                        t.stop++;
                        q.push(t);
                        obs[t.x][t.y] = t.stop;
                        vis[t.x][t.y] = 1;
                    }
                }
                else if (map[t.x][t.y] == 1 && t.stop < k && t.stop < obs[t.x][t.y]){
                    t.stop++;
                    q.push(t);
                    obs[t.x][t.y] = t.stop;
                }
                
            }
        }
    }
    return -1;
}

int main(){
    int T; cin >> T;
    while (T--){
        cin >> m >> n >> k;
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                cin >> map[i][j];
        cout << bfs() << endl;
    }
    return 0;
}