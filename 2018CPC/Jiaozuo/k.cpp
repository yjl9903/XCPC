#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxs = 10000 + 5;
const int maxn = 20 + 5;

int n, q, v[maxn], c[maxn], dp[maxn][maxs];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; i++) scanf("%d%d", v + i, c + i), c[i] = (1 << c[i]) - 1;

        ms(dp, 0); dp[0][0] = 1;
        for (int i = 1; i <= n; i++){
            // for (int j = 10000; j >= 0; j--){
            //     dp[i][j] = dp[i - 1][j];
            //     if (j < v[i]) continue;
            //     for (int l = 1; l < (1 << c[i]); l++){
            //         if (j >= l * v[i]){
            //             dp[i][j] += dp[i - 1][j - l * v[i]];
            //         }
            //         else break;
            //     }
            // }
            for (int j = 0; j < v[i]; j++){
                dp[i][j] = dp[i - 1][j];
            }
            for (int j = v[i]; j <= 10000; j++){
                dp[i][j] = dp[i][j - v[i]] + dp[i - 1][j];
                if (j >= c[i] * v[i]) dp[i][j] -= dp[i - 1][j - c[i] * v[i]];
            }
        }

        for (int i = 1; i <= n; i++, puts("")) for (int j = 0; j <= 5; j++) printf("%d ", dp[i][j]);

        while (q--){
            int x; scanf("%d", &x);
            printf("%d\n", dp[n][x]);
        }
    }
    return 0;
}