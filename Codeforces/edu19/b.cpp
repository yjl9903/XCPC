#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const ll inf = 1ll << 60;

int n, a[maxn];

int main(){
    scanf("%d", &n); for (int i = 0; i < n; i++) scanf("%d", a + i);
    sort(a, a + n); 
    ll sum1 = 0, sum2 = 0, maxs = -inf;
    for (int i = n - 1; i >= 0; i--){
        if (a[i] > 0 && a[i] % 2 == 0){ 
            sum2 += 1ll * a[i];
        }
        else if (abs(a[i]) % 2 == 1){
            sum1 += 1ll * a[i];
            if (abs(sum1) % 2ll == 1ll && sum1 >= maxs) maxs = sum1;
        }
    }
    printf("%I64d", maxs + sum2);
    return 0;
}