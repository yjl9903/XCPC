#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 120 + 5;

int c1[maxn], c2[maxn], n, dp[maxn];

int main(){
    // 母函数
    c1[0] = 1;
    for (int i = 1; i < maxn; i++){
        for (int j = 0; j < maxn; j += i){
            for (int k = 0; j + k < maxn; k++){
                c2[j + k] += c1[k];
            }
        }
        for (int j = 0; j < maxn; j++){
            c1[j] = c2[j]; c2[j] = 0;
        }
    }
    // DP: dp[i]表示组成i的方案数
    dp[0] = 1;
    for (int i = 1; i < maxn; i++){
        for (int j = 0; i + j < maxn; j++){
            dp[j + i] += dp[j];
        }
    }
    while (cin >> n){
        // cout << c1[n] << endl;
        cout << dp[n] << endl;
    }
    return 0;
}