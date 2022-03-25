#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;
const ll mod = 1e9 + 7;

int n, m;
ll dp[maxn][maxn] = {0};

int main(){
    ios::sync_with_stdio(false);
    dp[0][0] = 1;
    for (int i = 0; i < maxn; i++){
        for (int j = 0; j < maxn; j++){
            if (i) dp[i][j] = (dp[i][j] + dp[i - 1][j]) % mod;
            if (j) dp[i][j] = (dp[i][j] + dp[i][j - 1]) % mod;
        }
    }
    while (cin >> n >> m){
        ll a = dp[n][m] * dp[n][m] % mod, b = dp[n - 1][m + 1] * dp[n + 1][m - 1] % mod;
        cout << (a + mod - b) % mod << endl;
    }
    return 0;
}