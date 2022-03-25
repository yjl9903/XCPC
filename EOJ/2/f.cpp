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
const int maxn = 1000000 + 5;

int n, m, a[maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    sort(a, a + n);
    ll sum1 = 0, sum2 = 0;
    for (int i = 0; i < m; i++) sum1 += a[i], sum2 += 1ll * a[i] * a[i];
    ll ans = 1ll * m * sum2 - sum1 * sum1;
    for (int i = m; i < n; i++) {
        sum1 -= a[i - m]; sum2 -= 1ll * a[i - m] * a[i - m];
        sum1 += a[i]; sum2 += 1ll * a[i] * a[i];
        ans = min(ans, 1ll * m * sum2 - sum1 * sum1);
    }
    cout << ans << endl;
    return 0;
}