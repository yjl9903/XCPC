// PKu1014 Dividing
// 多重背包优化

#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10 + 5;
const int maxm = 500000 + 5;
const int inf = 1 << 30;

int v[maxn], dp[maxm];

int main(){
    int kase = 0;
    while (true){
        for (int i = 1; i <= 6; i++)
            cin >> v[i];
        int flag = 1, sum = 0;
        for (int i = 1; i <= 6; i++)
            if (v[i])
                flag = 0, sum += i * v[i];
        if (flag)
            return 0;
        if (kase)
            cout << endl;
        cout << "Collection #" << ++kase << ":\n";
        if (sum % 2){
            cout << "Can't be divided.\n";
            continue;
        }
        int w = sum / 2;
        // fill(dp, dp + maxm, inf); dp[0] = 1;
        // for (int i = 1; i <= 6; i++){
        //     for (int j = w; j >= i; j--){
        //         for (int k = 1; k <= v[i]; k++){
        //             if (j >= i * k){
        //                 dp[j] = min(dp[j], dp[j - k * i] + k);
        //             }
        //             else break;
        //         }
        //     }
        // }
        ms(dp, -1); dp[0] = 0;
        for (int i = 1; i <= 6; i++){
            for (int j = 0; j <= w; j++){
                if (dp[j] >= 0)
                    dp[j] = v[i];
                else{
                    if (j < i || dp[j - i] <= 0)
                        dp[j] = -1;
                    else
                        dp[j] = dp[j - i] - 1;
                }
            }
        }
        if (dp[w] < 0){
            cout << "Can't be divided.\n";
        }
        else{
            cout << "Can be divided.\n";
        }
    }
    return 0;
}