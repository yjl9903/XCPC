#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 1000 + 5;

int n, dp[maxn][maxn], pre[maxn][maxn], suf[maxn][maxn];

int main(){
    scanf("%d", &n);
    dp[1][1] = 1; dp[2][1] = 1; dp[2][2] = 0;
    pre[1][1] = 1; pre[2][1] = 1; pre[2][2] = 1; pre[2][3] = 1;
    suf[1][1] = 1; suf[2][0] = 1; suf[2][1] = 1; suf[2][2] = 0;
    for (int i = 3; i <= n; i++) {
        if (i % 2) {
            for (int j = i; j >= 1; j--) {
                dp[i][j] = pre[i - 1][j - 1];
                suf[i][j] = (suf[i][j + 1] + dp[i][j]) % mod;
            }
            suf[i][0] = suf[i][1];
        } else { 
            for (int j = 1; j <= i; j++) {
                dp[i][j] = suf[i - 1][j];
                pre[i][j] = (pre[i][j - 1] + dp[i][j]) % mod;
            }
            pre[i][i + 1] = pre[i][i];
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) ans = (ans + dp[n][i]) % mod;
    cout << ans << endl;
    return 0;
}