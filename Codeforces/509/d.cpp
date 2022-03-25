#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;
const int inf = 1 << 30;

int n, h, l[maxn], r[maxn], dt[maxn], len[maxn];

int main(){
    scanf("%d%d", &n, &h);
    for (int i = 0; i < n; i++) scanf("%d%d", l + i, r + i);
    if (n == 1){
        printf("%d", r[0] - l[0] + h); return 0;
    }
    for (int i = n - 2; i >= 0; i--) dt[i] = dt[i + 1] - l[i + 1] + r[i];
    for (int i = n - 1; i >= 0; i--) len[i] = len[i + 1] + r[i] - l[i];
    int ans = -inf;
    for (int i = 0; i < n; i++){
        if (h > -dt[i]) ans = max(ans, h + len[i]);
        else {
            int k = lower_bound(dt, dt + n, dt[i] + h) - dt;
            ans = max(ans, h + len[i] - len[k]);
        }
    }
    printf("%d", ans);
    return 0;
}