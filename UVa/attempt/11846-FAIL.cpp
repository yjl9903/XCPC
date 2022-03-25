#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20 + 5;

int map[maxn][maxn], res[maxn][maxn], n, k, cnt;
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void show(){
    for (int i = 0; i < n; i++, cout << endl)
        for (int j = 0; j < n; j++)
            cout << res[i][j] << ' ';
    cout << endl;
}

int dfs(int x, int y, int tot, int sum){
    if (sum == 0){
        // show();
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) 
            if (map[i][j] && !res[i][j]){
                res[i][j] = tot + 1; 
                if (dfs(i, j, tot + 1, map[i][j] - 1))
                    return 1;
                res[i][j] = 0;
                return 0;
            }
        // show();
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (!res[i][j]) return 0;
        // show(); cout << tot << endl;
        return 1;
    }
    int tx, ty;
    for (int i = 0; i < 4; i++){
        tx = x + dir[i][0]; ty = y + dir[i][1];
        if (tx < 0 || ty < 0 || tx >= n || ty >= n) continue;
        if (res[tx][ty] || map[tx][ty]) continue;
        res[tx][ty] = tot; 
        if (dfs(tx, ty, tot, sum - 1)) return 1;
        res[tx][ty] = 0;
    }
    return 0;
}

int main(){
    while (cin >> n >> k){
        if (!n && !k) return 0;
        for (int i = 0; i < n; i++){
            char s[maxn]; cin >> s;
            for (int j = 0; j < n; j++){
                if (s[j] == '.') map[i][j] = 0;
                else map[i][j] = s[j] - '0';
            }
        }
        cnt = 1; ms(res, 0); int flag = 0;
        for (int i = 0; i < n && !flag; i++) for (int j = 0; j < n && !flag; j++) if (map[i][j] && !res[i][j]){
            res[i][j] = 1;
            dfs(i, j, 1, map[i][j] - 1);
            flag = 1;
        }
        show();
        // for (int i = 0; i < n; i++, cout << endl)
        //     for (int j = 0; j < n; cout << char(res[i][j++] - 1 + 'A'));
        
    }
    return 0;
}