#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;
const int maxk = 1000 + 5;

bool check[maxn][maxn][maxk], vis[maxn][maxn][maxk], map[maxn][maxn];
int n, m, k, d;
int dir[5][2] = {-1, 0, 1, 0, 0, -1, 0, 1, 0, 0};
int cd[maxn], ct[maxn], cv[maxn], cx[maxn], cy[maxn];
struct node{
    int x, y, d;
    node(int a, int b, int c):x(a), y(b), d(c){};
};

void show(int t){
    for (int i = 0; i <= m; i++, cout << endl)
        for (int j = 0; j <= n; j++)
            cout << check[i][j][t];
    cout << endl;
}

int bfs(){
    ms(vis, 0);
    queue<node> q;
    q.emplace(0, 0, 0); vis[0][0][0] = 1;
    while (!q.empty()){
        node t = q.front(); q.pop();
        if (t.x == m && t.y == n) return t.d;
        // cout << t.x << ' ' << t.y << ' ' << t.d << endl;
        for (int i = 0; i < 5; i++){
            node x = {t.x + dir[i][0], t.y + dir[i][1], t.d + 1};
            // cout << x.x << ' ' << x.y << ' ' << x.d << endl;
            if (x.x < 0 || x.y < 0 || x.x > m || x.y > n) continue;
            if (!vis[x.x][x.y][x.d] && map[x.x][x.y] && t.d <= d && check[x.x][x.y][x.d]){
                vis[x.x][x.y][x.d] = 1;
                q.push(x);
            }
        }
    }
    return 0;
}

int main(){
    while (cin >> m >> n >> k >> d){
        ms(map, 1); ms(check, 1);
        for (int i = 0; i < k; i++){
            char x[2]; cin >> x;
            switch(x[0]){
                case 'N': cd[i] = 0; break;
                case 'S': cd[i] = 1; break;
                case 'W': cd[i] = 2; break;
                case 'E': cd[i] = 3; break;
            }
            cin >> ct[i] >> cv[i] >> cx[i] >> cy[i];
            map[cx[i]][cy[i]] = 0;
        }
        for (int i = 0; i < k; i++){
            int x = cx[i], y = cy[i], t = 0;
            while (t <= d){
                int flag = 0;
                if (dir[cd[i]][0]){
                    for (int j = x + dir[cd[i]][0]; /* j != x + dir[cd[i]][0] * cv[i] &&  */j >= 0 && j <= m; j += dir[cd[i]][0]){
                        if (!map[j][y]) flag = 1; 
                        // cout << j << ' ' << j << endl;
                        if (j == x + dir[cd[i]][0] * cv[i]) break;
                    }
                }
                if (dir[cd[i]][1]){
                    for (int j = y + dir[cd[i]][1]; /* j != y + dir[cd[i]][1] * cv[i] &&  */j >= 0 && j <= n; j += dir[cd[i]][1]){
                        if (!map[x][j]) flag = 1;
                        // cout << x << ' ' << j << endl;
                        if (j == y + dir[cd[i]][1] * cv[i]) break;
                    }
                }
                int tt = t;
                while (tt <= d){
                    check[x][y][tt] = 0;
                    tt += ct[i];
                }
                x += dir[cd[i]][0] * cv[i];
                y += dir[cd[i]][1] * cv[i];
                if (flag || x < 0 || y < 0 || x > m || y > n)
                    break;
                t++;
            }
        }
        // for (int i = 0; i <= d; i++)
        //     show(i);
        int flag = bfs();
        if (flag) cout << flag << endl;
        else cout << "Bad luck!\n";
    }
    return 0;
}