#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 2000 + 5;
const ll mod = 998244353;

int n, m, k;
ll dp[maxn][maxn];

int main(){
    cin >> n >> m >> k;
    dp[1][0] = m;
    for (int i = 2; i <= n; i++) {
        dp[i][0] = dp[i - 1][0];
        for (int j = 1; j < i; j++) {
            dp[i][j] = (dp[i - 1][j] + (m - 1) * dp[i - 1][j - 1] % mod) % mod;
        }
    }
    cout << dp[n][k] % mod << endl;
    return 0;
}