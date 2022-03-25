#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 30000 + 5;

int n, d[maxn], dp[maxn][4];

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", d + i);
    for (int i = 1; i <= n; i++){
        dp[i][1] = dp[i - 1][1];
        dp[i][2] = min(dp[i - 1][1], dp[i - 1][2]);
        dp[i][3] = min(dp[i][2], dp[i - 1][3]);
        if (d[i] == 1) dp[i][2]++, dp[i][3]++;
        if (d[i] == 2) dp[i][1]++, dp[i][3]++;
        if (d[i] == 3) dp[i][1]++, dp[i][2]++;
    }
    int ans = min(dp[n][1], min(dp[n][2], dp[n][3]));
    ms(dp, 0);
    for (int i = 1; i <= n; i++){
        dp[i][1] = dp[i - 1][1];
        dp[i][2] = min(dp[i - 1][1], dp[i - 1][2]);
        dp[i][3] = min(dp[i][2], dp[i - 1][3]);
        if (d[i] == 3) dp[i][2]++, dp[i][3]++;
        if (d[i] == 2) dp[i][1]++, dp[i][3]++;
        if (d[i] == 1) dp[i][1]++, dp[i][2]++;
    }
    int res = min(dp[n][1], min(dp[n][2], dp[n][3]));
    printf("%d\n", min(res, ans));
    return 0;
}