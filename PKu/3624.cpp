#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 3410 + 5;
const int maxm = 13000 + 5;

int n, m, w[maxn], d[maxn], dp[maxm];

int main(){
    while (~scanf("%d%d", &n, &m)){
        for (int i = 1; i <= n; i++) scanf("%d%d", &w[i], &d[i]);
        ms(dp, 0);
        for (int i = 1; i <= n; i++){
            for (int j = m; j >= w[i]; j--)
                dp[j] = max(dp[j], dp[j - w[i]] + d[i]);
        }
        printf("%d\n", dp[m]);
    }
    return 0;
}