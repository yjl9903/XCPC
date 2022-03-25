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
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, m, a[maxn], b[maxn], p[maxn], q[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        for (int i = 1; i <= m; i++) scanf("%d", b + i);
        multiset<int> v1[2], v2[2];
        for (int i = 1, p; i <= n; i++) {
            scanf("%d", &p); v1[p].insert(a[i]);
        }
        for (int i = 1, p; i <= m; i++) {
            scanf("%d", &p); v2[p].insert(b[i]);
        }
        int ans = 0;
        for (int x: v1[0]) {
            auto it = v2[1].lower_bound(x);
            if (it == v2[1].begin()) continue;
            it--; ans++; v2[1].erase(it);
        }
        for (int x: v1[1]) {
            auto it = v2[0].upper_bound(x);
            if (it == v2[0].end()) continue;
            ans++; v2[0].erase(it);
        }
        printf("%d\n", ans);
    }
    return 0;
}