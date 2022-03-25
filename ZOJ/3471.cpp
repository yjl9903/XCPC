#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10 + 5;

int v[maxn][maxn], n, dp[1 << 10];

int main(){
    while (cin >> n && n){
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> v[i][j];
        ms(dp, 0); int ans = 0;
        for (int s = 0; s < (1 << n); s++){
            for (int i = 0; i < n; i++) if ((s & (1 << i)) == 0)
                for (int j = 0; j < n; j++) if ((s & (1 << j)) == 0 && i != j){
                    // cout << dp[s | (1 << i)] << ' ' << dp[s] + v[j][i] << ' ';
                    dp[s | (1 << i)] = max(dp[s | (1 << i)], dp[s] + v[j][i]);
                    // cout << dp[s | (1 << i)] << endl;
                } 
        }
            
        for (int s = 0; s < (1 << n); s++)
            ans = max(ans, dp[s]);
        cout << ans << endl;
    }
    return 0;
}