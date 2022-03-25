#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int a, b, c, d;

int main(){
    while (~scanf("%d%d%d%d", &a, &b, &c, &d)){
        int s1 = (a - 1) / 2, s2 = b / 2;
        int s3 = (c - 1) / 1009, s4 = d / 1009;
        int s5 = (a - 1) / 2018, s6 = b / 2018;
        int s7 = (c - 1) / 2018, s8 = d / 2018;
        int a1 = (a - 1) / 1009, a2 = b / 1009;
        int a3 = (c - 1) / 2, a4 = d / 2;
        ll ans = 1ll * (s2 - s1 - s6 + s5) * (s4 - s3 - s8 + s7) + 1ll * (a2 - a1 - s6 + s5) * (a4 - a3 - s8 + s7) + 1ll * (s6 - s5) * (d - c + 1) + 1ll * (s8 - s7) * (b - a + 1) - 1ll * (s6 - s5) * (s8 - s7);
        printf("%lld\n", ans);
    }
    return 0;
}