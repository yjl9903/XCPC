#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 80 + 5;

int n, m, p;
int dp[maxn * maxn][maxn][maxn] = {0};

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d%d", &n, &m, &p);
        dp[1][1][1] = n * m % p;
        for (int k = n * m - 1, c = 2; c <= n * m; k--, c++){
             for (int i = 1; i <= n; i++){
                for (int j = 1; j <= m; j++){
                    if (i * j <= c - 1) continue;
                    int& t = dp[c][i][j];
                    t = (1ll * dp[c - 1][i - 1][j] * j * (n - i + 1) % p) % p;
                    t = (t + 1ll * dp[c - 1][i][j - 1] * i * (m - j + 1) % p) % p;
                    t = (t + 1ll * dp[c - 1][i][j] * (i * j - c + 1) % p) % p;
                }
            }
        }
        printf("%d\n", dp[n * m][n][m]);
    }
    return 0;
}