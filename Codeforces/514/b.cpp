#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m;
char map[maxn][maxn];
bool vis[maxn][maxn];

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%s", map[i]);
    for (int i = 0; i + 2 < n; i++){
        for (int j = 0; j + 2 < m; j++){
            if (map[i][j] == '.') continue;
            if (map[i][j + 1] == '.') continue;
            if (map[i][j + 2] == '.') continue;
            if (map[i + 1][j] == '.') continue;
            if (map[i + 1][j + 2] == '.') continue;
            if (map[i + 2][j] == '.') continue;
            if (map[i + 2][j + 1] == '.') continue;
            if (map[i + 2][j + 2] == '.') continue;
            for (int k = 0; k < 3; k++) vis[i][j + k] = vis[i + 2][j + k] = 1;
            vis[i + 1][j] = vis[i + 1][j + 2] = 1;
        }
    }
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++){
        if (map[i][j] == '.') continue;
        if (!vis[i][j]) {
            puts("NO"); return 0;
        }
    }
    puts("YES");
    return 0;
}