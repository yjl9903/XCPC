#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << "debug -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 100 + 5;

struct node{
    int x, y, b, p, d;
};

int n, m, sx, sy, ex, ey, dis[maxn][maxn][6];
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
bool vis[maxn][maxn][6];
char map[maxn][maxn];

int bfs(){
    ms(dis, -1); int ans = -1;
    queue<node> q; q.push(node{sx, sy, 0, 0, 0});
    ms(vis, 0);
    while (!q.empty()){
        node t = q.front(); q.pop();
        if (t.x == ex && t.y == ey) {
            if (ans == -1) ans = t.d;
            else ans = min(ans, t.d);
        }
        // if (vis[t.x][t.y][t.b]) continue;
        // vis[t.x][t.y][t.b] = 1;
        // dbg(t.x, t.y, t.b);
        for (int i = 0; i < 4; i++){
            int tx = t.x + dir[i][0], ty = t.y + dir[i][1];
            if (tx < 0 || ty < 0 || tx >= n || ty >= m) continue;
            // if (vis[tx][ty][t.b]) continue;
            int td = t.d + 1; if (t.p) td--;
            if (map[tx][ty] == '.'){
                if (dis[tx][ty][t.b] == -1 || dis[tx][ty][t.b] > td){
                    dis[tx][ty][t.b] = td;
                    q.push(node{tx, ty, t.b, 0, td});
                }
            }
            else if (map[tx][ty] == '#'){
                if (!t.b) continue;
                if (dis[tx][ty][t.b - 1] == -1 || dis[tx][ty][t.b - 1] > td + 1){
                    dis[tx][ty][t.b - 1] = td + 1;
                    q.push(node{tx, ty, t.b - 1, 0, td + 1});
                }
            }
            else if (map[tx][ty] == 'B'){
                int tot = t.b + 1; if (tot > 5) tot = 5;
                if (dis[tx][ty][tot] == -1 || dis[tx][ty][tot] > td){
                    dis[tx][ty][tot] = td;
                    q.push(node{tx, ty, tot, 0, td});
                }
            }
            else if (map[tx][ty] == 'P'){
                // dbg(dis[tx][ty][t.b]);
                if (dis[tx][ty][t.b] == -1 || dis[tx][ty][t.b] > td){
                    dis[tx][ty][t.b] = td;
                    q.push(node{tx, ty, t.b, 1, td});
                }
            }
        }
    }
    return ans;
}

int main(){
    while (~scanf("%d%d", &n, &m)){
        if (!n && !m) return 0;
        for (int i = 0; i < n; i++) scanf("%s", map[i]);
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++){
            if (map[i][j] == 'S') sx = i, sy = j, map[i][j] = '.';
            if (map[i][j] == 'T') ex = i, ey = j, map[i][j] = '.'; 
        }
        printf("%d\n", bfs());
    }
    return 0;
}