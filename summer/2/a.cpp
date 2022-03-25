#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int q;
// map<int, set<int> > mp;
set<PII> st;

int main() {
    while (scanf("%d", &q) == 1) {
        if (q == 0) break;
        // mp.clear();
        st.clear();
        int op, a, b;
        for (int i = 1; i <= q; i++) {
            scanf("%d%d%d", &op, &a, &b);
            if (op == -1) {
                // mp[a].erase(b);
                st.erase({a, b});
            } else if (op == 0) {
                ll ans = 0;
                for (auto& x: st) {
                    ans = max(ans, 1ll * a * x.first + 1ll * b * x.second);
                }
                // for (auto& x: mp) {
                //     ll tot = 1ll * x.first * a;
                //     if (x.second.size() == 0) continue;
                //     ans = max(ans, tot + 1ll * *x.second.begin() * b);
                //     ans = max(ans, tot + 1ll * *x.second.rbegin() * b);
                // }
                printf("%lld\n", ans);
            } else {
                // mp[a].insert(b);
                st.insert({a, b});
            }
        }
    }
    return 0;
}