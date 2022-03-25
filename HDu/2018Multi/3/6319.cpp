#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>
#include <utility>
#include <queue>
#include <deque>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 10000000 + 5;

int n, m, k, p, q, r, mod, a[maxn];
PII dq[maxn];
// int ans[maxn][2]; 

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d%d%d%d%d%d", &n, &m, &k, &p, &q, &r, &mod);
        for (int i = 1; i <= k; i++) scanf("%d", &a[i]);
        for (int i = k + 1; i <= n; i++) a[i] = (1ll * p * a[i - 1] + 1ll * q * i + r) % mod;
        ll A = 0, B = 0;
        int t = 0, h = 1;
        for (int i = n; i > n - m + 1; i--){
            while (h <= t && a[i] >= dq[t].first) t--;
            dq[++t] = make_pair(a[i], i);
        }
        for (int i = n - m + 1; i > 0; i--){
            while (h <= t && a[i] >= dq[t].first) t--;
            dq[++t] = make_pair(a[i], i);
            if (dq[h].second - i >= m) h++;
            // ans[i][0] = t - h + 1;
            // ans[i][1] = dq[h].first;
            A += dq[h].first ^ i;
            B += (t - h + 1) ^ i;
        }
        // for (int i = 1; i <= n - m + 1; i++){
        //     printf("%d %d\n", ans[i][0], ans[i][1]);
        // }
        printf("%lld %lld\n", A, B);
    }
    return 0;
}