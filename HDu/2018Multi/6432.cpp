#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;
const int mod = 998244353;

ll f[maxn];

int main(){
    f[0] = 1; f[1] = 0; f[2] = 0; f[3] = 1; f[4] = 1;
    for (int i = 5, g = -1; i < maxn; i++, g = -g){
        f[i] = ((1ll * (i - 2) * f[i - 1] % mod + 1ll * (i - 1) * f[i - 2] % mod) % mod - g + mod) % mod;
        // printf("%d %lld\n", i, f[i]);
    }
    int n;
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &n);
        printf("%lld\n", f[n]);
    }
    return 0;
}