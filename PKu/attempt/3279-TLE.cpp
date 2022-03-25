#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 15 + 5;

int m, n, maxd, map[maxn][maxn], cnt[maxn][maxn];
int dir[5][2] = {{0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int dfs(int d, int p){
    if (d == maxd){
        // cout << endl;
        // for (int i = 0; i < m; i++, cout << endl) for (int j = 0; j < n; j++) cout << cnt[i][j] << ' ';
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) if (map[i][j]) return 0;
        return 1;
    }
    int tx = p / n, ty = p % n; 
    
    if (tx >= m || ty >= n) return 0;
    
    if (dfs(d, p + 1)) return 1;
    // else if (d == maxd - 1) return 0;
    // cout << tx << ' ' << ty << endl;
    int t[maxn][maxn]; memcpy(t, map, sizeof map);
    for (int i = tx; i < m; i++) for (int j = (i == tx ? ty : 0); j < n; j++){
        cnt[i][j]++;
        memcpy(map, t, sizeof map);
        for (int t = 0; t < 5; t++){
            int x = i + dir[t][0], y = j + dir[t][1];
            if (x < 0 || y < 0 || x >= m || y >= n) continue;
            map[x][y] = map[x][y] ^ 1;
        }
        if (dfs(d + 1, i * n + j)) return 1;
        cnt[i][j]--;
    }
    return 0;
}

int main(){
    while (cin >> m >> n){
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) cin >> map[i][j];
        int flag = 0;
        for (maxd = 0; !flag; maxd++){
            ms(cnt, 0);
            flag = dfs(0, 0);
        }
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                if (j) cout << ' ';
                cout << cnt[i][j];
            }
            cout << endl;
        }
    }
    return 0;
}