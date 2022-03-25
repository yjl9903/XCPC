#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20 + 5;

int n, a[maxn], b[maxn], st[maxn];
ll ans, dp[1 << 21];

int main(){
    scanf("%d", &n);
    for (int m, x, i = 0; i < n; i++){
        scanf("%d%d%d", a + i, b + i, &m);
        int t = 0;
        while (m--){
            scanf("%d", &x); x--;
            t = t | (1 << x);
        }
        st[i] = t;
    }
    ms(dp, -1);
    int ss = 1 << n; dp[0] = 0;
    for (int s = 1; s < ss; s++){
        int k = 0;
        for (int i = 0; i < n; i++) if (s & (1 << i)) k++;
        for (int i = 0; i < n; i++) if (s & (1 << i)){
            int u = s ^ (1 << i);
            if (dp[u] != -1 && (u & st[i]) == st[i]){
                ll t = dp[u] + k * a[i] + b[i];
                dp[s] = max(dp[s], t);
                ans = max(ans, dp[s]);
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}