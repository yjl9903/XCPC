#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, c, v[maxn], w[maxn], dp[maxn];

int main(){
    int T; cin >> T;
    while (T--){
        cin >> n >> c;
        for (int i = 0; i < n; i++) cin >> v[i];
        for (int i = 0; i < n; i++) cin >> w[i];
        ms(dp, 0);
        for (int i = w[0]; i <= c; i++) dp[i] = v[0];
        for (int i = 1; i < n; i++){
            for (int j = c; j >= 0; j--){
                if (j >= w[i]) dp[j] = max(dp[j - w[i]] + v[i], dp[j]);
            }
        }
        cout << dp[c] << endl;
    }
    return 0;
}