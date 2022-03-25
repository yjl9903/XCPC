#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10 + 5;

int n, m, dp[maxn][maxn] = {0};

int main(){
    dp[0][0] = 1;
    for (int i = 1; i <= 10; i++){
        for (int j = 0; j <= 10; j++){
            if (j >= i) dp[i][j] = dp[i][j - i] + dp[i - 1][j];
            else dp[i][j] = dp[i - 1][j];
        }
    }
    int T; cin >> T;
    while (T--){
        cin >> n >> m; cout << dp[m][n] << endl;
    }
    return 0;
}