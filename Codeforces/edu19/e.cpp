#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const int maxm = 400;

int n, q, a[maxn];
int dp[maxn][maxm];

int main(){
    scanf("%d", &n); for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int m = sqrt(1.0 * n);
    for (int j = 1; j <= m; j++){
        for (int i = n; i > 0; i--){
            if (i + a[i] + j > n) dp[i][j] = 1;
            else dp[i][j] = dp[i + a[i] + j][j] + 1;
        }
    }
    scanf("%d", &q);
    while (q--){
        int p, k; scanf("%d%d", &p, &k);
        if (k <= m){
            printf("%d\n", dp[p][k]);
        }
        else {
            int ans = 0;
            while (p <= n){
                p += a[p] + k;
                ans++;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}