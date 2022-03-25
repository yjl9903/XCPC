#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, m, vis[2][maxn];

int main(){
    while (~scanf("%d%d", &n, &m)){
        ms(vis, 0);
        for (int i = 0; i < m; i++){
            int x, y; scanf("%d%d", &x, &y);
            vis[0][x] = vis[1][y] = 1;
        }
        int res = 2 * n - (n % 2);
        for (int i = 1; i <= n; i++){
            if (n % 2 && i == n / 2 + 1){
                if (vis[1][i] || vis[0][i])
                    res--;
                continue;
            }
            if (vis[1][i]) res--;
            if (vis[0][i]) res--;
        }
        printf("%d\n", res);
    }
    return 0;
}