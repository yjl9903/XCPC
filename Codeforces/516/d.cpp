#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 2000 + 5;

char map[maxn][maxn];
int n, m, r, c, x, y;
int vis[maxn][maxn], ml[maxn][maxn], mr[maxn][maxn];
PII dis[maxn][maxn];
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

struct node{
    int x, y;
    node(){}
    node(int xx, int yy):x(xx), y(yy){};
};

int bfs(){
    queue<PII> q; q.emplace(r, c);
    int ans = 0; dis[r][c] = make_pair(0, 0);
    while (!q.empty()){
        PII t = q.front(); q.pop();
        vis[t.first][t.second] = 1;
        for (int i = 0; i < 4; i++){
            int tx = t.first + dir[i][0], ty = t.second + dir[i][1];
            if (tx < 1 || ty < 1 || tx > n || ty > m || map[tx][ty] == '*') continue;
            PII k = dis[t.first][t.second];
            if (i == 1) k.first++;
            if (i == 3) k.second++;
            if (k.first > y) continue;
            if (k.second > x) continue;
            if (dis[tx][ty] > k){
                dis[tx][ty] = k;
                q.emplace(tx, ty); 
            }
        }
    }
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) ans += vis[i][j];
    // for (int i = 1; i <= n; puts(""), i++) for (int j = 1; j <= m; j++) cout << vis[i][j];
    return ans;
}

int main(){
    scanf("%d%d%d%d%d%d", &n, &m, &r, &c, &x, &y);
    for (int i = 1; i <= n; i++) scanf("%s", map[i] + 1);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) dis[i][j] = make_pair(1e9 + 7, 1e9 + 7);
    printf("%d\n", bfs());
    return 0;
}