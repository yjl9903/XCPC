#include <cstdio>
#include <cstring>
#include <algorithm>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

ll n, t, a[maxn], x[maxn], b[maxn];

int main(){
    scanf("%I64d%I64d", &n, &t);
    for (ll i = 1; i <= n; i++) scanf("%I64d", a + i);
    for (ll i = 1; i <= n; i++) scanf("%I64d", x + i);
    for (ll i = 1; i <= n; i++){
        if (i > x[i]) {
            puts("No"); return 0;
        }
    }
    // b[n] = a[n];
    for (ll i = 1; i <= n; i++){
        // if (x[i] == i) b[i] = max(a[i], b[i - 1] + 1);
        for (ll j = i + 1; j <= x[i]; j++){
            b[j - 1] = a[j];
        }
        b[x[i]] = max(a[x[i]], b[x[i] - 1] + 1);
        if (x[i] + 1 <= n && a[x[i] + 1] <= b[x[i]]){
            puts("No"); return 0;
        }
    }
    puts("Yes"); 
    for (int i = 1; i <= n; i++) printf("%I64d ", b[i] + t);
    return 0;
}