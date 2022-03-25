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
const int maxn = 1000000 + 5;

int n, k, a[maxn];

set<PII> st[maxn];
inline int lowbit(int x) { return x & -x; }
void update(int i, int x) {
    int j = i;
    for (; i <= n; i += lowbit(i)) {
        st[i].insert({x, j});
    }
}
int query(int i, int l) {
    int r = 0;
    for (; i > 0; i -= lowbit(i)) {
        while (!st[i].empty() && st[i].rbegin()->second < l) {
            auto it = st[i].end(); it--; st[i].erase(it);
        }
        if (!st[i].empty()) {
            r = max(r, st[i].rbegin()->first);
        }
    }
    return r;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int ans = 0;
    for (int i = 1; i <= k; i++) {
        int tot = query(a[i] - 1, 0);
        ans = max(ans, tot + 1);
        update(a[i], tot + 1);
    }
    printf("%d ", ans);
    for (int r = k + 1, l; r <= n; r++) {
        l = r - k + 1;
        int b = query(n + 1, l);
        int tot = query(a[r] - 1, l) + 1;
        printf("%d ", max(tot, b));
        update(a[r], tot);
    }
    return 0;
}