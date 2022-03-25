#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, a[maxn], b[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d%d", a + i, b + i);
        ll ans = 0, mt = b[1], pp = a[1];
        for (int i = 2; i <= n; i++) {
            ll tmp = min(1ll * b[i], min(ans, 1ll * a[i]));
            ans += tmp; a[i] -= tmp; b[i] -= tmp;

            ll mn1 = min(1ll * a[i], mt);
            ans += mn1; mt -= mn1; a[i] -= mn1;
            
            ll mn2 = min(1ll * b[i], pp);
            ans += mn2; pp -= mn2; b[i] -= mn2;
            
            mt += b[i]; pp += a[i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}