#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, m, s[maxn], p[maxn];
ll res[maxn], cost[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n,&m);
        for (int i = 0; i < n; i++){
            scanf("%d%d", &s[i], &p[i]);
            cost[i] = 1ll * s[i] * p[i];
        }
        for (int i = n - 1; i > 0; i--)
            if (cost[i - 1] > cost[i]) cost[i - 1] = cost[i];
        
        // for (int i = 0; i < n; i++) printf("%lld ", cost[i]); printf("\n");
        int x;
        while (m--){
            scanf("%d", &x);
            if (x >= s[n - 1]){
                printf("%lld\n", 1ll * x * p[n - 1]);
                continue;
            }
            int r = upper_bound(s, s + n, x) - s - 1;
            // cout << ' ' << r << endl;
            ll a = 1ll * p[r] * x;
            a = min(cost[r + 1], a);
            // for (int i = r + 1; i < n; i++)
            //     a = min(a, cost[i]);
            printf("%lld\n", a);
        }
    }
    return 0;
}