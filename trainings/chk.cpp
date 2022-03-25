#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int dp[maxn][maxn];

int cal(int x, int y){
    int a = (x - y) / (y + 1), b = (x - y) % (y + 1);
    return (y + 1 - b) * a * (a + 1) / 2 + b * (a + 1) * (a + 2) / 2;
}

int main(){
    int n = 450;
    for (int i = 0; i <= n; i++){
        dp[i][0] = i * (i + 1) / 2;
        for (int j = 1; j < i; j++){
            int x = 1 << 30;
            for (int k = 1; k < i; k++){
                for (int l = 0; l <= j - 1; l++){
                    x = min(x, dp[k - 1][l] + dp[i - k][j - 1 - l]);
                }
            }
            dp[i][j] = x;
            // cout << x << ' ';
        }
        // cout << endl;
    }
    for (int i = 1; i <= n; i++) for (int j = 1; j < i; j++){
        if (cal(i, j) != dp[i][j]) puts("No");
    }
    puts("Yes");
    return 0;
}