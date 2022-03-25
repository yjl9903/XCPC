#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, a[maxn], dp[maxn];

int main(){
    while (~scanf("%d", &n)){
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        // ms(dp, 0); dp[0] = dp[1] = 1;
        // int res = 0;
        // for (int i = 2; i <= n; i++){
        //     int len = 0;
        //     for (int j = 1; j < i; j++) if (a[j] < a[i]) len = max(len, dp[j]);
        //     dp[i] = len + 1;
        //     res = max(res, dp[i]);
        // }
        // printf("%d\n", res);
        fill(dp, dp + 1 + n, 1 << 30);
        int res = 1; dp[1] = a[1];
        for (int i = 2; i <= n; i++){
            // int p = lower_bound(dp + 1, dp + 1 + res, a[i]) - dp;
            // dp[p] = a[i];
            // res = max(res, p);
            if (a[i] > dp[res]) dp[++res] = a[i];
            else {
                int p = lower_bound(dp + 1, dp + 1 + res, a[i]) - dp;
                dp[p] = a[i];
            }
        }
        printf("%d\n", res);
    }
    return 0;
}