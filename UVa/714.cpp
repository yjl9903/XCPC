#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int k, m, a[maxn], last[maxn];

bool check(ll x){
    int i = 1, c = 1;
    ll s = 0;
    while (i <= m){
        s += a[i];
        if (s > x){
            s = 0; c++; i--;
        }
        i++;
    }
    return c <= k;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        ll sum = 0, l = 0, r, res = 0;
        scanf("%d%d", &m, &k);
        for (int i = 1; i <= m; i++) scanf("%d", &a[i]), sum += a[i], l = max(l, 1ll * a[i]);
        // sort(a + 1, a + 1 + m);
        r = sum;
        while (l < r){
            ll m = (l + r) >> 1;
            if (check(m)){
                res = r = m;
            }
            else {
                l = m + 1;
            }
        }
        // printf("%lld\n", res);
        ms(last, 0);
        ll t = 0;
        int re = k;
        for (int i = m; i > 0; i--){
            if (t + 1ll * a[i] > res || i < re){
                last[i] = 1; t = 1ll * a[i]; re--;
            }
            else t += 1ll * a[i];
        }
        for (int i = 1; i <= m - 1; i++){
            printf("%d ", a[i]);
            if (last[i]) printf("/ ");
        }
        printf("%d\n", a[m]);
    }
    return 0;
}