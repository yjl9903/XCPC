#include <bits/stdc++.h>

using namespace std;
const int mod = 1000000007;
const int MAXN = 4004;

int dp[MAXN][MAXN];

int main()
{
    int n;
    cin>>n;
    dp[0][0] = 1;
    for(int i = 1;i <= n+1;i++){
        dp[i][0] = dp[i-1][i-1];
        for(int j = 1;j <= i;j++){
            dp[i][j] = (dp[i][j-1]+dp[i-1][j-1])%mod;
        }
    }
    printf("%d\n",(dp[n+1][0]-dp[n][0]+mod)%mod);
    return 0;
}
