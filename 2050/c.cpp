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
const int maxn = 100000 + 5;

int ceil(int x, int k) {
    return x / k + (x % k == 0 ? 0 : 1);
}

int n, m, k, a, b, c;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d%d%d%d", &n, &m, &k, &a, &b, &c);
        ll ans = 1e18;
        for (int p = 0; p <= k; p++) {
            ll tot = 1ll * p * c, sx = 1e18, sy = 1e18;
            for (int i = 0; i <= n + k - p; i++) {
                ll x = 1ll * ceil(i, 2) * a + 1ll * ceil(n + k - p - i, 3) * b;
                sx = min(sx, x);
            }
            for (int i = 0; i <= m + k - p; i++) {
                ll y = 1ll * ceil(i, 2) * a + 1ll * ceil(m + k - p - i, 3) * b;
                sy = min(sy, y);
            }
            ans = min(ans, tot + sx + sy);
        }
        printf("%lld\n", ans);
    }
    return 0;
}