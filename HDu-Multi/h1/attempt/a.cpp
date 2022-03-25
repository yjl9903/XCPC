#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int fac[maxn], n, cnt = 0;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        cnt = 0;
        for (int i = 1; i * i <= n; i++){
            if (n % i == 0){
                fac[cnt++] = i;
                if (i * i != n) fac[cnt++] = n / i;
            }
        }
        sort(fac, fac + cnt);
        ll res = -1;
        for (int i = 0; i < cnt; i++){
            for (int j = i; j < cnt; j++){
                if (fac[i] + fac[j] >= n) break;
                int z = n - fac[i] - fac[j];
                if (n % z == 0){
                    ll t = 1ll * fac[i] * fac[j] * z;
                    res = max(res, t);
                }
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}