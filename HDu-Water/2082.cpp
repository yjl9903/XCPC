#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 30 + 5;

int a[maxn], dp[55];

int main(){
    int T; cin >> T;
    while (T--){
        for (int i = 1; i <= 26; i++) cin >> a[i];
        ms(dp, 0); dp[0] = 1;
        for (int i = 1; i <= 26; i++){
            for (int j = 50; j >= i; j--){
                for (int k = 1; k <= a[i]; k++){
                    if (j >= k * i) dp[j] += dp[j - k * i];
                }
            }
        }
        ll res = 0;
        for (int i = 1; i <= 50; i++) res += dp[i];
        cout << res << endl;
    }
    return 0;
}