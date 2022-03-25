// PKu1458 Common Subsequence
// LCS + 滚动数组

#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

char a[maxn], b[maxn];
int dp[2][maxn];

int main(){
    while (~scanf("%s%s", a + 1, b + 1)){
        int n = strlen(a + 1), m = strlen(b + 1), res = 0; ms(dp, 0);
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= m; j++){
                if (a[i] == b[j]){
                    dp[i % 2][j] = dp[(i + 1) % 2][j - 1] + 1;
                } 
                else dp[i % 2][j] = max(dp[(i + 1) % 2][j], dp[i % 2][j - 1]);
            }
        }
        printf("%d\n", dp[n % 2][m]);
    }
    return 0;
}