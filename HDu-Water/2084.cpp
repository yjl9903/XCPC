#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

int t[maxn][maxn], dp[maxn][maxn], n;

int main(){
    int T; cin >> T;
    while (T--){
        cin >> n; ms(dp, 0); ms(t, 0);
        for (int i = 1; i <= n; i++) for (int j = 1; j <= i; j++) cin >> t[i][j];
        dp[1][1] = t[1][1];
        for (int i = 2; i <= n; i++){
            for (int j = 1; j <= i; j++) 
                dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + t[i][j];
        }
        int res = 0;
        for (int i = 1; i <= n; i++) res = max(res, dp[n][i]);
        cout << res << endl;
    }
    return 0;
}