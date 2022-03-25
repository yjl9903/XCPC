#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 10 + 5;

int map[maxn][maxn], mark[maxn][maxn], n, m, ans, res;
int vis[maxn][maxn], vis2[maxn];
int cnt1, cnt2, nxt[maxn][maxn], color[maxn][maxn];
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
vector<int> appear;
vector<PII> farm[10];

int dfs(int x, int y, int t){
    if (mark[x][y]) return 1;
    mark[x][y] = 1;
    for (int i = 0; i < 4; i++){
        int tx = x + dir[i][0], ty = y + dir[i][1];
        if (tx < 0 || ty < 0 || tx >= n || ty >= m) continue;
        if (map[tx][ty] == t && !vis[tx][ty]){
            vis[tx][ty] = 1;
            if (dfs(tx, ty, t)) return 1;
        }
        else if (map[tx][ty] != t){
            mark[tx][ty] = 1;
        }
    }
    return 0;
}

int find(int p){
    int x = p / 11, y = p % 11;
    for (int i = 0; i < 4; i++){
        int tx = x + dir[i][0], ty = y + dir[i][1];
        if (tx < 0 || ty < 0 || tx >= n || ty >= m) continue;
        if (mark[tx][ty] || vis[tx][ty]) continue;
        vis[tx][ty] = 1;
        if (nxt[tx][ty] == -1 || find(nxt[tx][ty])){
            nxt[tx][ty] = p;
            return true;
        }
    }
    return false;
}
int match(){
    int sum = 0; ms(nxt, -1);
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (!mark[i][j] && ((i + j) % 2) == 1){
        ms(vis, 0);
        if (find(11 * i + j)) sum++;
    }
    return sum;
}

int main(){
    int T, kase = 0; cin >> T;
    while (T--){
        appear.clear(); ms(vis2, 0); res = 0;
        for (int i = 0; i < 10; i++) farm[i].clear();

        cin >> n >> m;
        for (int i = 0; i < n; i++){
            char s[maxn]; cin >> s;
            for (int j = 0; j < m; j++){
                if (s[j] == '.') map[i][j] = -1;
                else map[i][j] = s[j] - '0', vis2[map[i][j]] = 1;
            }
        }
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (map[i][j] != -1){
            farm[map[i][j]].push_back(make_pair(i, j));
        }
        for (int i = 0; i <= 10; i++) if (vis2[i]) appear.push_back(i);
        sort(appear.begin(), appear.end());

        for (int s = 0; s < (1 << appear.size()); s++){
            ms(vis, 0); ms(mark, 0); ans = 0;
            int flag = 0;
            for (int k = 0; k < appear.size(); k++) if (s & (1 << k)){
                int t = appear[k]; 
                for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (map[i][j] == t && !vis[i][j]){
                    vis[i][j] = 1; ans++;
                    if (dfs(i, j, t)) {
                        flag = 1; break;
                    }
                }
                if (flag) break;
            }
            if (flag) continue;
            for (int k = 0; k < appear.size(); k++) if ((s & (1 << k)) == 0){
                int t = appear[k];
                for (int i = 0; i < farm[t].size(); i++) {
                    PII x = farm[t][i];
                    mark[x.first][x.second] = 1;
                }
            }
            int sum = 0;
            for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (!mark[i][j]) sum++;
            ans += sum - match();
            res = max(res, ans);
        }
        cout << "Case #" << ++kase << ": ";
        cout << res << endl;
    }
    return 0;
}