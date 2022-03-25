#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m, map[maxn][maxn], vis[maxn][maxn] = {0};
char s[maxn];
struct node{
    int x, y, sz;
};
vector<node> v;

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++){
        scanf("%s", s);
        for (int j = 0; j < m; j++) 
            if (s[j] == '*') map[i][j] = 1;
            else map[i][j] = 0;
    }
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if (map[i][j]) {
        int k = 1;
        while (1){
            int flag = 0;
            if (i + k < n && map[i + k][j]) flag++;
            if (i - k >= 0 && map[i - k][j]) flag++;
            if (j + k < m && map[i][j + k]) flag++;
            if (j - k >= 0 && map[i][j - k]) flag++;
            if (flag != 4) break;
            k++;
        }
        if (k > 1) v.push_back({i, j, k - 1});
    }
    for (int i = 0; i < v.size(); i++) {
        int x = v[i].x, y = v[i].y;
        vis[x][y] = 1;
        for (int j = 1; j <= v[i].sz; j++) {
            vis[x + j][y] = vis[x - j][y] = vis[x][y + j] = vis[x][y - j] = 1;
        }
    }
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++){
        if (map[i][j] && !vis[i][j]){
            puts("-1"); return 0;
        }
    }
    printf("%d\n", v.size());
    for (int i = 0; i < v.size(); i++){
        printf("%d %d %d\n", v[i].x + 1, v[i].y + 1, v[i].sz);
    }
    return 0;
}