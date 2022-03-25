#include<iostream>
#include<cstring>
#include <algorithm>
#include <cstdio>
#include<cmath>
#include<vector>
#include<queue>
using ll = long long;
using namespace std;
const int N = 1111;
const int Mod = 0;
ll a[N];
int n,m,T;
int Read();
ll dp[N][100];
int gcd(int x,int y){
    return y ? gcd(y ,x % y) : x;
}
int main() {
    n = Read();
    for(int i = 1; i <= n; i++) a[i] = Read();
    for(int i = 1; i <= n; i++)
        for(int j = 0; j < 100; j++)
            dp[i][j] = 1e14;
    for(int i = 1; i <= 100; i++)
        dp[1][i] = abs(i - 50);
    for(int i = 2; i <= n; i++){
        for(int j = max(50 - a[i - 1] + 1,0ll); j <= 99; j++)
            for(int k = max(50 - a[i] + 1,0ll); k <= 99; k++)
               if(a[i] + k - 50 > 0 && a[i - 1] + j - 50 > 0){
                   int k1 = a[i] + k -50,k2 = a[i - 1] + j - 50;
                   if (gcd(a[i] + k - 50,a[i - 1] + j - 50) == 1){
                       dp[i][k] = min(dp[i][k],dp[i - 1][j] + abs(k - 50));
                   }
               }
    }
    ll ans = 1e14;
    for(int i = 0; i <= 99; i++)
        ans = min(ans,dp[n][i]);
    cout << ans << endl;
    return 0;
}

int Read()  {
    int val = 0, opt = 1; char ch;
    while (!isdigit(ch = getchar())) if (ch == '-') opt = -1;
    while (isdigit( ch )) (val *= 10) += ch - '0', ch = getchar();
    return val * opt;
}
