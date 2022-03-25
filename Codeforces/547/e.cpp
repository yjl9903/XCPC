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
const int maxn = 200000 + 5;
const ll inf = 1e18;

ll h, d[maxn], mn = 1e18; int n;

int main() {
    scanf("%I64d%d", &h, &n);
    for (int i = 1; i <= n; i++) scanf("%I64d", d + i), d[i] += d[i - 1], mn = min(mn, d[i]);
    for (int i = 0; i <= n; i++) if (h + d[i] <= 0) {
        printf("%d", i); return 0;
    }
    if (d[n] >= 0) return puts("-1"), 0;
    ll ans = inf;
    for (int i = 0; i <= n; i++) {
        ll r = h + d[i];
        ll t = r / (-d[n]); if (r % (-d[n])) t++;
        ans = min(ans, t * n + i);
    }
    if (ans == inf) return puts("-1"), 0;
    cout << ans << endl;
    return 0;
}