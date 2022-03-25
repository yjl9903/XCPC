#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 500 + 5;

int e, f, n, p[maxn], w[maxn], dp[10005];

int main(){
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--){
        cin >> e >> f >> n;
        for (int i = 1; i <= n; i++) cin >> p[i] >> w[i];
        fill(dp, dp + 10005, 1 << 30); dp[0] = 0;
        for (int i = 1; i <= n; i++) for (int j = w[i]; j <= f - e; j++){
            dp[j] = min(dp[j], dp[j - w[i]] + p[i]);
        }
        if (dp[f - e] == (1 << 30)){
            cout << "This is impossible.\n";
        }
        else {
            cout << "The minimum amount of money in the piggy-bank is " << dp[f - e] << ".\n";
        }
    }
    return 0;
}