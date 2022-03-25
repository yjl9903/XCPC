#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 50 + 5;
const int maxt = 200 + 5;
const int inf = 1 << 30;

int n, T, t[maxn], m1, m2;
bool have[maxt][maxn][2];
int dp[maxt][maxn];

int main(){
    int kase = 0;
    while (scanf("%d%d", &n, &T) == 2 && n){
        ms(have, 0); t[0] = 0;
        for (int i = 0; i < maxt; i++) for (int j = 0; j < maxn; j++) dp[i][j] = inf;
        for (int i = 1; i < n; i++) scanf("%d", &t[i]);
        scanf("%d", &m1);
        for (int i = 0; i < m1; i++){
            int x; scanf("%d", &x);
            for (int k = 1; k < n && x <= T; x += t[k], k++){
                have[x][k][0] = 1;
            }
        }
        scanf("%d", &m2);
        for (int i = 0; i < m2; i++){
            int x; scanf("%d", &x);
            for (int k = n; k > 1 && x <= T; k--, x += t[k]){
                have[x][k][1] = 1;
            }
        }
        
        dp[0][1] = 0;
        for (int i = 0; i <= T; i++){
            for (int j = 1; j <= n; j++){
                int tmp = 1 << 30;
                if (j > 1 && i >= t[j - 1] && have[i - t[j - 1]][j - 1][0]) tmp = dp[i - t[j - 1]][j - 1];
                if (j < n && i >= t[j] && have[i - t[j]][j + 1][1]) tmp = min(tmp, dp[i - t[j]][j + 1]);
                if (i) dp[i][j] = min(dp[i - 1][j] + 1, tmp);
            }
        }
        int res = dp[T][n];
        printf("Case Number %d: ", ++kase);
        if (res == inf) printf("impossible\n");
        else printf("%d\n", res);
    }
    return 0;
}