#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 20 + 5;

int map[maxn][maxn], vis[maxn][maxn], res[2 * maxn], t[2 * maxn], R, C, maxd, cnt, flag;
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int dfs(int x, int y, int d, int check){
    for (int i = 0; i < d; i++) 
        if (t[i] < res[i]) return 0;
        else if (t[i] > res[i]) break;
    if (d == maxd){
        int tt = 0;
        for (int i = 0; i < maxd; i++)
            if (t[i] > res[i]){
                tt = 1; break;
            }
            else if (t[i] < res[i]){
                tt = 0; break;
            }
        if (tt) for (int i = 0; i < maxd; i++) res[i] = t[i];
        flag = 1;
        return 1;
    }
    vector<PII> choose; 
    int tx, ty;
    for (int i = 0; i < 4; i++){
        tx = x + dir[i][0], ty = y + dir[i][1];
        if (tx < 0 || ty < 0 || tx >= R || ty >= C) continue;
        if (vis[tx][ty] || !map[tx][ty]) continue;
        choose.push_back(make_pair(map[tx][ty], i));
    }
    sort(choose.begin(), choose.end());
    for (int i = choose.size() - 1; i >= 0; i--){
        tx = x + dir[choose[i].second][0], ty = y + dir[choose[i].second][1];
        t[d] = choose[i].first; vis[tx][ty] = 1;
        dfs(tx, ty, d + 1, check);
        vis[tx][ty] = 0;
    }
    return 0;
}

int main(){
    while (cin >> R >> C && R && C){
        cnt = 0; ms(res, 0);
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++){
                char x; cin >> x;
                if (x == '#') map[i][j] = 0;
                else map[i][j] = x - '0', cnt++;
            }
        flag = 0;
        for (maxd = cnt; !flag; maxd--){
            for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) if (map[i][j]){
                ms(vis, 0); t[0] = map[i][j]; vis[i][j] = 1;
                dfs(i, j, 1, 1);
            }
        }
        for (int i = 0; i < maxd + 1; i++)
            cout << res[i];
        cout << endl;
    }
    return 0;
}