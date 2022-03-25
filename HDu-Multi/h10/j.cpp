#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<ll,ll> PLL;
const ll inf = 1ll << 62;
const int maxn = 100000 + 5;

int n, m, k;
ll x[maxn][5], y[maxn][5], a[maxn], b[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d%d", &n, &m, &k);
        int ss = 1 << k;
        for (int i = 0; i < n; i++){
            scanf("%lld", &a[i]);
            for (int j = 0; j < k; j++){
                scanf("%lld", &x[i][j]);
            }
        }
        for (int i = 0; i < m; i++){
            scanf("%lld", &b[i]);
            for (int j = 0; j < k; j++){
                scanf("%lld", &y[i][j]);
            }
        }

        ll ans = -inf;
        for (int s = 0; s < ss; s++){
            ll ma = -inf, mi = inf;
            for (int i = 0; i < n; i++){
                ll t = 0;
                for (int j = 0; j < k; j++){
                    if (s & (1 << j)) t += x[i][j];
                    else t -= x[i][j];
                }
                ma = max(1ll * a[i] + t, ma);
            }
            for (int i = 0; i < m; i++){
                ll t = 0;
                for (int j = 0; j < k; j++){
                    if (s & (1 << j)) t += y[i][j];
                    else t -= y[i][j];
                }
                mi = min(-1ll * b[i] + t, mi);
            }
            ans = max(ans, ma - mi);
        }
        printf("%lld\n", ans);
    }
    return 0;
}