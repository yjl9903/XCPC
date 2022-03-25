#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 500000 + 5;
const int inf = 1 << 30;

int n;
ll a[maxn];

int main(){
    scanf("%d", &n);
    ll ans = 0, ma = -inf, mi = inf, ak = -1, ik = -1;
    for (int i = 0; i < n; i++) {
        scanf("%I64d", a + i);
        if (a[i] > ma) ma = a[i], ak = i;
        else if (a[i] < mi) mi = a[i], ik = i;
    }
    if (n == 1){
        printf("%I64d", a[0]); return 0;
    }
    else if (n == 2){
        printf("%I64d", max(a[0] - a[1], a[1] - a[0])); return 0;
    }
    for (int i = 0; i < n; i++){
        if (i != ak && i != ik){
            if (a[i] < 0) ans -= a[i];
            else ans += a[i];
        }
        else if (i == ak) ans += ma;
        else if (i == ik) ans -= mi;
    }
    printf("%I64d", ans);
    return 0;
}