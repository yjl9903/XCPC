#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m, dp[1 << 16];

int main(){
    while (cin >> n >> m){
        int ss = (1 << n) - 1;
        ms(dp, -1);
        while (m--){
            int k, s = 0; cin >> k;
            while (k--){
                int x; cin >> x;
                s = s | (1 << (x - 1));
            }
            int rest = ss ^ s;
            dp[s] = max(dp[s], 1);
            for (int i = rest; i; i = (i - 1) & rest){
                if (dp[i] != -1) dp[s | i] = max(dp[s | i], dp[i] + 1);
            }
        }
        int ans = 0;
        for (int i = 0; i <= ss; i++) ans = max(ans, dp[i]);
        cout << ans << endl;
    }
    return 0;
}