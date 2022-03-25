#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10000 + 5;

int m, k[maxn], a, b;
ll sum1[maxn] = {0}, sum2[maxn] = {0}, sum3[maxn] = {0};

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d%d", &m, &a, &b);
        int s = 0;
        for (int i = 1; i <= m; i++) scanf("%d", &k[i]), s += k[i];
        for (int i = 1; i <= m; i++) sum1[i] = sum1[i - 1] + 1ll * (i - 1) * k[i];
        for (int i = 1; i <= m; i++) sum2[i] = sum2[i - 1] + k[i];
        for (int i = 1; i <= m; i++) sum3[i] = sum3[i - 1] + 1ll * (m - i) * k[i];

        int ans = 0;
        ll tot = 1ll << 62, sd = 0, su = 0;
        for (int i = 1; i <= m; i++) su += 1ll * (i - 1) * i / 2 * k[i] + 1ll * i * a * k[i];
        for (int i = 1; i <= m; i++){
            sd += b * sum2[i - 1] + sum3[i - 1] - (m - i + 1) * sum2[i - 1]; 
            su -= a * (sum2[m] - sum2[i - 1]) + sum1[m] - sum1[i] - (i - 1) * (sum2[m] - sum2[i]);
            // printf("%d %d\n", sd, su);
            if (sd + su < tot) tot = sd + su, ans = i;
        }
        printf("%d\n", ans);
    }
    return 0;
}