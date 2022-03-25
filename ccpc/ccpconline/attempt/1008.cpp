#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <cassert>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, k, a[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        sort(a + 1, a + 1 + n);
        reverse(a + 1, a + 1 + n);
        ll ans = k;
        multiset<ll> ok, ev;
        ev.insert(k + a[1]);
        for (int i = 2; i <= n; i++) {
            if (ev.empty()) {
                
            } else {

            }
        }

        // multiset<int> st;
        // ll ans = k, last = a[1];
        // for (int i = 2; i <= n; i++) {
        //     if (last >= k) {
        //         last -= k; ans += k;
        //         st.insert(a[i]);
        //     } else {
        //         if (st.empty()) {
        //             ans += k;
        //             last = a[i];
        //         } else {
        //             ans += last + k;
        //             auto it = st.end(); it--;
        //             last = max(*it - k, 0);
        //             st.erase(it);
        //             st.insert(a[i]);
        //         }
        //     }
        // }
        // ans += last;
        // for (auto x: st) ans += x;
        // printf("%lld\n", ans);
    }
    return 0;
}