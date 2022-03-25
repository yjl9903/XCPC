#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20 + 5;
const int inf = 1 << 30;

int r, c, sr, sc, tr, tc, vp, vs, vt;
char map[maxn][maxn];

struct node{
    int x, y, d;
    bool operator<(const node& b)const{
        return d > b.d;
    }
};
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int dis[maxn][maxn], vis[maxn][maxn];
int dijkstra(){
    ms(vis, 0);
    for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) dis[i][j] = inf;
    dis[sr][sc] = 0;
    priority_queue<node> q; q.push({sr, sc, 0});
    while (!q.empty()){
        node t = q.top(); q.pop();
        if (vis[t.x][t.y]) continue;
        vis[t.x][t.y] = 1;
        for (int i = 0; i < 4; i++){
            int x = t.x + dir[i][0], y = t.y + dir[i][1];
            if (x < 0 || x >= r || y < 0 || y >= c) continue;
            if (map[x][y] == '@') continue;
            int td = t.d;
            if (map[x][y] == 'T') td += vt;
            if (map[x][y] == '.') td += vs;
            if (map[x][y] == '#') td += vp;
            if (!vis[x][y] && dis[x][y] > td){
                dis[x][y] = td;
                q.push({x, y, td});
            }
        }
    }
    return dis[tr][tc];
}

int main(){
    int kase = 0;
    while (~scanf("%d%d", &r, &c)){
        scanf("%d%d%d", &vp, &vs, &vt);
        for (int i = 0; i < r; i++) scanf("%s", map[i]);
        scanf("%d%d%d%d", &sr, &sc, &tr, &tc);
        int ans = dijkstra();
        if (ans == inf) ans = -1;
        printf("Case %d: %d\n", ++kase, ans);
    }
    return 0;
}