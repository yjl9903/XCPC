#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, m, a[maxn], c[maxn], vis[maxn];
set<PII> st;

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) scanf("%d", c + i);
    for (int i = 1; i <= n; i++) {
        st.insert({c[i], i});
    }
    int flag = 0;
    for (int i = 1, t, d; i <= m; i++) {
        scanf("%d%d", &t, &d);
        if (flag) {
            puts("0"); continue;
        }
        if (a[t] - d >= 0) {
            printf("%I64d\n", 1ll * c[t] * d);
            a[t] -= d;
            if (a[t] == 0) {
                st.erase({c[t], t});
            }
        } else {
            ll sum = 1ll * c[t] * a[t];
            d -= a[t]; a[t] = 0;
            if (st.count({c[t], t})) st.erase({c[t], t});
            while (d > 0) {
                if (st.empty()) {
                    flag = 1; break;
                }
                PII t = *st.begin();
                int id = t.second;
                if (a[id] - d >= 0) {
                    sum += 1ll * c[id] * d;
                    a[id] -= d; d = 0;
                    if (a[id] == 0) {
                        st.erase({c[id], id});
                    }
                } else {
                    sum += 1ll * c[id] * a[id];
                    d -= a[id]; a[id] = 0;
                    if (st.count({c[id], id})) st.erase({c[id], id});
                }
            }
            if (flag) puts("0");
            else printf("%I64d\n", sum);
        }
    }
    return 0;
}