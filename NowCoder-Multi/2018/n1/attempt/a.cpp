#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const int mod = 1e9 + 7;

ll dp[maxn][maxn][3];

int main(){
    ios::sync_with_stdio(false);
    dp[1][1][0] = dp[1][1][1] = dp[1][1][2] = 1;
    for (int i = 2; i <= 1000; i++) {
        dp[1][i][2] = ((dp[1][i - 1][0] + dp[1][i - 1][1]) % mod + dp[1][i - 1][2]) % mod;
        dp[1][i][1] = (dp[1][i - 1][0] + dp[1][i - 1][1]) % mod;
        dp[1][i][0] = dp[1][i - 1][0] % mod;
        dp[i][1][2] = ((dp[i - 1][1][0] + dp[i - 1][1][1]) % mod + dp[i - 1][1][2]) % mod;
        dp[i][1][1] = (dp[i - 1][1][0] + dp[i - 1][1][1]) % mod;
        dp[i][1][0] = (dp[i - 1][1][0]) % mod;
    }
    for (int i = 2; i <= 1000; i++){
        for (int j = 2; j <= 1000; j++){
            // dp[i][j][2] = (9 * dp[i - 1][j - 1][0] % mod + 4 * dp[i - 1][j - 1][1] % mod + dp[i - 1][j - 1][2] % mod) % mod;
            // dp[i][j][1] = (4 * dp[i - 1][j - 1][0] % mod + dp[i - 1][j - 1][1] % mod) % mod;
            // dp[i][j][0] = dp[i - 1][j - 1][0] % mod;
            dp[i][j][2] = (dp[i - 1][j][2] * dp[i][j - 1][2] % mod + dp[i - 1][j][1] * dp[i][j - 1][1] % mod + 1) % mod;
            dp[i][j][1] = (dp[i - 1][j][1] * dp[i][j - 1][1] % mod + 1) % mod;
            dp[i][j][0] = 1;
        }
    }
    int n, m;
    while (cin >> n >> m){
        int ans = (dp[n][m][0] + dp[n][m][1] + dp[n][m][2]) % mod;
        cout << ans << endl;
    }
    return 0;
}