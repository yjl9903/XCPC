#include <iostream>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 10 + 5;

int n, m, map[maxn][maxn], mark[maxn][maxn], vis[maxn][maxn], res, ans, maxd;
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}, used[15];
vector<PII> ani[10];
vector<int> choose;

int dfs(int x, int y, int k){
    if (mark[x][y]) return 1;
    mark[x][y] = 1;
    for (int i = 0; i < 4; i++){
        int tx = x + dir[i][0], ty = y + dir[i][1];
        if (tx < 0 || ty < 0 || tx >= n || ty >= m) continue;
        if (map[tx][ty] == k) continue;
        mark[tx][ty] = 1;
    }
    
    for (int i = 0; i < 4; i++){
        int tx = x + dir[i][0], ty = y + dir[i][1];
        if (tx < 0 || ty < 0 || tx >= n || ty >= m) continue;
        if (!vis[tx][ty] && map[tx][ty] == k){
            vis[tx][ty] = 1; 
            if (dfs(tx, ty, k)) return 1;
        }
    }
    return 0;
}

// int init(int p, int d){
//     if (d > maxd){
//         for (int i = 0; i < choose.size(); i++) cout << choose[i] << ' ';
//         cout << endl;

//         ms(mark,0); ms(vis, 0); ans = 0;
//         for (int k = 0; k < choose.size(); k++){
//             for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (map[i][j] == choose[k] && !vis[i][j]){
//                 // cout << i << ' ' << j << ' ' << choose[k] << endl;
//                 vis[i][j] = 1; 
//                 if (dfs(i, j, choose[k])) return 0;
//                 ans++;
//             }
//         }

//         // for (int i = 0; i < choose.size(); i++) cout << choose[i] << ' ';
//         // cout << endl;
//         // for (int i = 0; i < n; cout << endl, i++) for (int j = 0; j < m; j++) cout << mark[i][j] << ' '; cout << endl;

//         res = max(res, ans);
//         return 0;
//     }
//     init(p, d + 1);
//     for (int i = p; i <= maxd; i++){
//         if (ani[i].size()){
//             choose.push_back(i);
//             // cout << i << ' ';
//             init(i + 1, d + 1);
//             choose.pop_back();
//         }
//     }
// }

int main(){
    int T, kase = 0; cin >> T;
    while (T--){
        cin >> n >> m; maxd = 0;
        for (int i = 0; i < n; i++){
            char s[maxn]; cin >> s;
            for (int j = 0; j < m; j++){
                if (s[j] == '.') map[i][j] = -1;
                else map[i][j] = s[j] - '0', maxd = max(maxd, map[i][j]);
            }
        }
        res = 0;
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++){
            if (map[i][j] >= 0){
                ani[map[i][j]].push_back(make_pair(i, j));
            }
        }

        // choose.clear(); ans = res = 0; ms(used, 0);
        // init(0, 0);

        for (int s = 0; s < (1 << mmax); s++){
            ms(mark, 0); int ans = 0, flag = 0;
            for (int k = 0; k < mmax; k++){
                if (s & (1 << k)){
                    // for (int i = 0; i < ani[k].size(); i++){
                    //     PII x = ani[k][i];
                    //     // cout << x.first << ' ' << x.second << endl;
                    //     if (mark[x.first][x.second] == 1){
                    //         flag = 1; break;
                    //     }
                    //     mark[x.first][x.second] = 1;
                    //     for (int i = 0; i < 4; i++){
                    //         int tx = x.first + dir[i][0], ty = x.second + dir[i][1];
                    //         if (tx < 0 || ty < 0 || tx >= n || ty >= m) continue;
                    //         if (map[tx][ty] == k) continue;
                    //         mark[tx][ty] = 1;
                    //     }
                    // }
                    ms(vis, 0);
                    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (map[i][j] == k && !vis[i][j]){
                        vis[i][j] = 1; ans++;
                        if (dfs(i, j, k)){
                            flag = 1; break;
                        }
                    }
                }
                if (flag) break;
            }
            if (flag) continue;
            for (int k = 0; k < mmax; k++){
                if ((s & (1 << k)) == 0){
                    for (int i = 0; i < ani[k].size(); i++){
                        PII x = ani[k][i];
                        mark[x.first][x.second] = 1;
                    }
                }
            }
            cout << s << endl;
            for (int i = 0; i < n; cout << endl, i++) for (int j = 0; j < m; j++) cout << mark[i][j] << ' '; cout << endl;
            res = max(res, ans);
        }

        cout << "Case #" << ++kase << ": ";
        cout << res << endl;
    }
    return 0;
}