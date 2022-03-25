#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 2000 + 5;

char map[maxn][maxn];
int n, m, vis[maxn][maxn], cnt[maxn][2];

int check(int t){
    for (int i = 1; i <= m / 2; i++){
        if (map[t][i] != map[t][m + 1 - i])
            return m / 2 - i + 1;
    }
    return 0;
}
int check2(int t){
    for (int i = 1; i <= n / 2; i++){
        if (map[i][t] != map[n + 1 - i][t])
            return n / 2 - i + 1;
    }
    return 0;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        ms(vis, 0); ms(cnt, 0);
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%s", map[i] + 1);
        if (check(1) || check(n) || check2(1) || check2(m)){
            printf("0\n"); continue;
        }
        
        for (int i = 2; i <= n / 2; i++) for (int j = 2; j <= m / 2; j++){
            char c = map[i][j];
            if (c != map[n - i + 1][j]) vis[i][j] = 1;
            if (c != map[i][m - j + 1]) vis[i][j] = 1;
            if (c != map[n - i + 1][m - j + 1]) vis[i][j] = 1;
            if (vis[i][j]) cnt[j][0] = 1, cnt[i][1] = 1;
        }
        // for (int i = 2; i <= n / 2; i++, puts("")) for (int j = 2; j <= m / 2; j++) printf("%d", vis[i][j]);

        int res = 0;
        for (int i = 2; i <= n / 2; i++) {
            for (int j = 2; j <= m / 2; j++){
                res++;
                if (cnt[j][0]) break;
            }
            if (cnt[i][1]) break;
        }
        printf("%d\n", res);
    }
    return 0;
}