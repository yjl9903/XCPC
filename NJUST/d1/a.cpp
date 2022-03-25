#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef unsigned long long ll;
const int maxn = 2000017 + 5;

ll n, a[maxn], b[maxn];

int main(){
    a[1] = 1; b[1] = 1;
    for (ll i = 2; i < maxn; i++) a[i] = a[i - 1] + i;
    for (ll i = 2; i < maxn; i++) b[i] = b[i - 1] + a[i];
    int T; scanf("%d", &T);
    while (T--){
        scanf("%llu", &n);
        if (n == 1){
            puts("1 1 1"); continue;
        }
        ll x = lower_bound(b + 1, b + maxn, n) - b;
        printf("%llu ", x);
        n -= b[x - 1];
        x = lower_bound(a + 1, a + maxn, n) - a;
        printf("%llu %llu\n", x, n - a[x - 1]);
    }
    return 0;
}