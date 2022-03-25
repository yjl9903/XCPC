#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, m, a[maxn];
ll dp[maxn];  

int main(){
    int kase = 0;
    while (~scanf("%d%d", &n, &m), n || m){
        ms(a, 0); ms(dp, 0); dp[0] = 1;
        for (int i = 1, x; i <= n; i++) scanf("%d", &x), a[x]++;
        for (int i = 1; i <= n; i++){
            if (!a[i]) continue;
            for (int j = n; j >= 1; j--){
                for (int k = 1; k <= a[i]; k++){
                    if (j >= k) dp[j] += dp[j - k];
                    else break;
                }
            }
        }
        printf("Case %d:\n", ++kase);
        int r;
        while (m--){
            scanf("%d", &r);
            printf("%lld\n", dp[r]);
        }
    }
    return 0;
}