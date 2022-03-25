#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, dp[2][maxn], pre[2][maxn], suf[2][maxn];

int main(){
    // scanf("%d", &n);
    n = 100000; printf("1,");
    dp[1][1] = 1; pre[1][1] = 1; suf[1][1] = 1; 
    for (int i = 2, f = 0; i <= n; i++, f ^= 1) {
        ll sum = 0;
        if (i % 2) {
            for (int j = i; j >= 1; j--) {
                dp[f][j] = pre[f ^ 1][j - 1];
                sum = (sum + dp[f][j]) % mod;
                suf[f][j] = (suf[f][j + 1] + dp[f][j]) % mod;
            }
            suf[f][0] = suf[f][1];
        } else { 
            for (int j = 1; j <= i; j++) {
                dp[f][j] = suf[f ^ 1][j];
                sum = (sum + dp[f][j]) % mod;
                pre[f][j] = (pre[f][j - 1] + dp[f][j]) % mod;
            }
            pre[f][i + 1] = pre[f][i];
        }
        printf("%lld,", sum);
    }
    // int ans = 0;
    // for (int i = 1; i <= n; i++) ans = (ans + dp[n][i]) % mod;
    // cout << ans << endl;
    return 0;
}