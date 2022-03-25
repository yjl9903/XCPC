#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int c[10], dp[maxn];

int main(){
    int kase = 0;
    while (1){
        int s = 0;
        for (int i = 1; i <= 6; i++) {
            scanf("%d", c + i);
            s += i * c[i];
        }
        if (s == 0) return 0;
        if (kase) puts("");
        if (s % 2){
            printf("Collection #%d:\nCan't be divided.\n", ++kase);
            continue;
        }
        s /= 2; 
        ms(dp, -1); dp[0] = 0;
        for (int i = 1; i <= 6; i++){
            for (int j = 0; j <= s; j++){
                if (dp[j] >= 0) dp[j] = c[i];
                else {
                    if (j < i || dp[j - i] <= 0) dp[j] = -1;
                    else dp[j] = dp[j - i] - 1;
                }
            }
        }
        printf("Collection #%d:\n", ++kase);
        if (dp[s] < 0){
            puts("Can't be divided.");
        }
        else {
            puts("Can be divided.");
        }
    }
    return 0;
}