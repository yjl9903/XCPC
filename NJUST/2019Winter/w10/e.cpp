#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 998244353;
const int maxn = 500000 + 5;

int n, x[maxn], k;
PII a[maxn];
ll pre[maxn], pre2[maxn];

int main() {
    scanf("%d", &n); for (int i = 1; i <= n; i++) scanf("%d", &a[i].first), a[i].second = i;
    scanf("%d", &k);
    sort(a + 1, a + 1 + n);
    if (k == 2) {
        int ans = 1e9, p;
        for (int i = 1; i < n; i++) if (a[i + 1].first - a[i].first < ans) ans = a[i + 1].first - a[i].first, p = i;
        cout << a[p].second << ' ' << a[p + 1].second << endl;
        return 0;
    }
    for (int i = 1; i < n; i++) pre[i] = pre[i - 1] + a[i + 1].first - a[i].first;
    for (int i = 1; i < n; i++) pre2[i] = pre2[i - 1] + 1ll * i * (a[i + 1].first - a[i].first);

    // for (int i = 1; i < n; i++) cout << a[i + 1].first  - a[i].first << ' '; cout << endl << endl;
    // for (int i = 1; i < n; i++) cout << pre[i] << ' '; cout << endl << endl;
    // for (int i = 1; i < n; i++) cout << pre2[i] << ' '; cout << endl << endl;
    
    ll tot = 0; for (int i = 1; i < k; i++) tot += 1ll * (a[i + 1].first - a[i].first) * i * (k - i);
    ll ans = tot; int p = 1;
    // cout << ans << endl;
    k--;
    for (int i = 1; i + k < n; i++) {
        tot += 1ll * k * (a[i + k].first - a[i + k - 1].first - a[i + 1].first + a[i].first);
        tot += 2ll * (pre2[i + k - 1] - pre2[i]);
        tot -= 1ll * (2 * i + k - 1) * (pre[i + k - 1] - pre[i]);
        // cout << "?: " << tot << endl;
        // cout << "?\n";
        // cout << k << ' ' << a[i + k].first - a[i + k - 1].first
        // cout << 1ll * k * (a[i + k].first - a[i + k - 1].first - a[i + 1].first + a[i].first) << endl;
        // cout << 2ll * (pre2[i + k - 1] - pre2[i]) << endl;
        // cout << 1ll * (2 * i + k - 1) * (pre[i + k - 1] - pre[i]) << endl;

        if (tot < ans) {
            ans = tot; p = i;
        }
    }
    // cout << ans << endl;
    for (int i = p; i - p <= k; i++) printf("%d ", a[i].second);
    return 0;
}