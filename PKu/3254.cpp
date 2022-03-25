#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 12 + 5;
const int mod = 100000000;

int dp[maxn][1 << 13], n, m;    
int map[maxn];

inline int check(int x){ // 1： 有重复
    return x & (x << 1);
}

int main(){
    while (~scanf("%d%d", &m, &n)){
        ms(map, 0); ms(dp, 0);
        for (int i = 1; i <= m; i++){
            for (int j = 1; j <= n; j++){
                int x; scanf("%d", &x);
                if (!x){
                    map[i] += (1 << (j - 1));
                }
            }
            // cout << map[i] << endl;
        }
        for (int s = 0; s < (1 << n); s++){
            if ((s & map[1]) == 0 && check(s) == 0) dp[1][s] = 1;
            // cout << s << ' ' << dp[1][s] << endl;
            // cout << s << ' ' << (s & map[1]) << ' ' << check(s) << ' ' << ((s & map[1] == 0) && !check(s)) << ": "<< dp[1][s] << endl;
        }
        for (int i = 2; i <= m; i++){
            for (int s = 0; s < (1 << n); s++){
                if ((s & map[i]) == 0 && !check(s)){
                    int sum = 0;
                    for (int ss = 0; ss < (1 << n); ss++){
                        if ((ss & map[i - 1]) == 0 && !check(ss) && (ss & s) == 0){
                            sum = (dp[i - 1][ss] + sum) % mod;
                        }
                    }
                    dp[i][s] = sum;
                    // printf("%d\n", sum);
                }
            }
        }
        int res = 0;
        for (int s = 0; s < (1 << n); s++) res = (res + dp[m][s]) % mod;
        printf("%d\n", res);
    }
    return 0;
}