#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxs = 10000 + 5;
const int maxn = 20 + 5;

int n, q, v[maxn], c[maxn], dp[maxs];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; i++) scanf("%d%d", v + i, c + i);

        ms(dp, 0); dp[0] = 1;
        for (int i = 1; i <= n; i++){
            for (int j = 10000; j >= v[i]; j--){
                for (int l = 0; l < c[i]; l++){
                    if (j >= (1 << l) * v[i]){
                        dp[j] += dp[j - (1 << l) * v[i]];
                    }
                    else break;
                }
            }
        }

        while (q--){
            int x; scanf("%d", &x);
            printf("%d\n", dp[n][x]);
        }
    }
    return 0;
}