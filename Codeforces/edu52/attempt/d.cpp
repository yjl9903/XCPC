#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
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
const int maxn = 10 + 5;

int a[maxn][maxn], n, r = 1 << 30, r2 = 1 << 30;
PII loc[maxn * maxn];
int dir[8][2] = {1, 2, 2, 1, -1, 2, 2, -1, 1, -2, -2, 1, -1, -2, -2, -1};

void dfs(int x, int y, int k, int c, int c2, int t){
    if (t > n * n) {
        // r = min(r, c); 
        if (c < r || (c == r && c2 < r2)) r = c, r2 = c2;
        return;
    }
    if (c >= r) return;
    
    if (k == 0){
        int flag = 0;
        for (int i = 0; i < 8; i++){
            int tx = x + dir[i][0], ty = y + dir[i][1];
            if (tx < 1 || ty < 1 || tx > n || ty > n) continue;
            if (a[tx][ty] == t){
                dfs(tx, ty, 0, c + 1, c2, t + 1); break;
            }
            for (int j = 0; j < 8; j++){
                tx = x + dir[i][0] + dir[j][0];
                ty = y + dir[i][1] + dir[j][1];
                if (tx < 1 || ty < 1 || tx > n || ty > n) continue;
                if (a[tx][ty] == t){
                    dfs(tx, ty, 0, c + 2, c2, t + 1); flag = 1; break;
                }

                for (int k = 0; k < 8; k++){
                    tx = x + dir[i][0] + dir[j][0] + dir[k][0];
                    ty = y + dir[i][1] + dir[j][1] + dir[k][1];
                    if (tx < 1 || ty < 1 || tx > n || ty > n) continue;
                    if (a[tx][ty] == t){
                        dfs(tx, ty, 0, c + 3, c2, t + 1); flag = 1; break;
                    }
                }
                if (flag) break;
            }
            if (flag) break;
        }
    }
    else if (k == 1){
        int tx = loc[t].first, ty = loc[t].second;
        if (tx != x && ty != y) dfs(tx, ty, 1, c + 2, c2, t + 1); 
        else dfs(tx, ty, 1, c + 1, c2, t + 1);
    }
    else if (k == 2){
        int tx = loc[t].first, ty = loc[t].second;
        if (abs(tx - x) == abs(ty - y)) dfs(tx, ty, 2, c + 1, c2, t + 1);
        else dfs(tx, ty, 2, c + 2, c2, t + 1);
    }
    for (int i = 0; i < 3; i++) if (i != k) dfs(x, y, i, c + 1, c2 + 1, t);
}

int main(){
    scanf("%d", &n); int tx, ty;
    for (int i = 1; i <= 3; i++) for (int j = 1; j <= 3; j++) {
        scanf("%d", &a[i][j]);
        if (a[i][j] == 1) tx = i, ty = j;
        loc[a[i][j]] = make_pair(i, j);
    }
    for (int i = 0; i < 3; i++) dfs(tx, ty, i, 0, 0, 2);
    cout << r << ' ' << r2;
    return 0;
}