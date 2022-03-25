#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, s, a[maxn];

int main(){
    scanf("%d%d", &n, &s);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    sort(a, a + n);
    int k = upper_bound(a, a + n, s) - a;
    ll ans = 0;
    // printf("%d\n", k);
    if (k > n / 2){
        for (int i = n / 2; i < k; i++){
            ans += 1ll * abs(s - a[i]);
        }
    }
    else{
        for (int i = k; i <= n / 2; i++){
            ans += 1ll * abs(a[i] - s);
        }
    }
    printf("%I64d", ans);
    return 0;
}