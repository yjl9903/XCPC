#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10000 + 5;

char s[maxn], p[] = "seven";
ll dp[6][maxn];

int main(){
    while (cin >> s){
        int len = strlen(s);
        ms(dp, 0);
        for (int i = 0; i < len; i++) if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] - 'A' + 'a';
        // for (int i = 0; i < len; i++){
        //     if (s[i] == 's') dp[0][i]++;
        // }
        for (int i = 0; i < len; i++) dp[0][i] = 1;
        dp[1][0] = (s[0] == 's' ? 1 : 0);
        for (int k = 1; k <= 5; k++){
            for (int i = 1; i < len; i++){
                if (s[i] == p[k - 1]) 
                    dp[k][i] = dp[k - 1][i - 1] + dp[k][i - 1];
                else
                    dp[k][i] = dp[k][i - 1];
            }
        }
        // for (int i = 0; i < 6; i++, cout << endl) for (int j = 0; j < len; j++) cout << dp[i][j] << ' ';
        cout << dp[5][len - 1] << endl;
    }
    return 0;
}