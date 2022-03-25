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

ll ceil(ll x, ll y) {
    return x / y + (x % y == 0 ? 0 : 1);
}

int n, a[maxn];

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        a[0] = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        for (int i = n; i >= 1; i--) a[i] -= a[i - 1];
        ll ans = 1, t = 1;
        for (int i = n - 1; i >= 1; i--) {
            ll tot = ceil(1ll * a[i] * t, a[i + 1]);
            ans += tot; t = tot;
        }
        printf("Case #%d: %lld\n", ++kase, ans);
    }
    return 0;
}