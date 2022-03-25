#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

int map[maxn][maxn], N, M, vis[maxn][maxn], cnt;
int dir[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

void dfs(int x, int y){
    int tx, ty;
    for (int i = 0; i < 8; i++){
        tx = x + dir[i][0], ty = y + dir[i][1];
        if (tx < 0 || ty < 0 || tx >= N || ty >= M) continue;
        if (!vis[tx][ty] && map[tx][ty]){
            vis[tx][ty] = 1;
            dfs(tx, ty);
        }
    }
}

int main(){
    ms(vis, 0); cnt = 0;
    cin >> N >> M; char s[maxn];
    for (int i = 0; i < N; i++){
        cin >> s;
        for (int j = 0; j < M; j++)
            if (s[j] == 'W')
                map[i][j] = 1;
            else    
                map[i][j] = 0;
    }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (!vis[i][j] && map[i][j])
                dfs(i, j), cnt++;
    cout << cnt;
    return 0;
}