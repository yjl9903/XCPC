#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<ll,ll> PLL;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n;
PLL a[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%lld%lld", &a[i].first, &a[i].second);
        }
        sort(a + 1, a + 1 + n);
        ll ans = 8e18;
        multiset<ll> pre, suf;
        for (int i = 1; i <= n; i++) pre.insert(a[i].second);
        for (int i = n; i >= 1; i--) {
            pre.erase(pre.find(a[i].second));
            auto it = suf.end();
            if (it == suf.begin()) {
                auto it = pre.upper_bound(a[i].first);
                if (it != pre.end()) {
                    ans = min(ans, *it - a[i].first);
                }
                if (it != pre.begin()) {
                    it--;
                    ans = min(ans, a[i].first - *it);
                }
            } else {
                it--; ll mx = *it;
                if (mx > a[i].first) ans = min(ans, mx - a[i].first);
                else {
                    ans = min(ans, a[i].first - mx);
                    auto it = pre.upper_bound(a[i].first);
                    if (it != pre.end()) {
                        ans = min(ans, max(*it, mx) - a[i].first);
                    }
                    if (it != pre.begin()) {
                        it--; ans = min(ans, a[i].first - max(*it, mx));
                    }
                }
            }
            suf.insert(a[i].second);
        }
        printf("%lld\n", ans);
    }
    return 0;
}