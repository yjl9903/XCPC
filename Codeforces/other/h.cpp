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

inline int lowbit(int x) {
    return x & -x;
}

int n, q, a[maxn];

struct BIT {
    ll a[maxn];
    void clear(int n) {
        for (int i = 0; i <= n; i++) a[i] = 0;
    }
    void update(int i, int x) {
        for (; i <= n; i += lowbit(i)) a[i] += x;
    }
    ll query(int i) {
        ll r = 0;
        for (; i > 0; i -= lowbit(i)) r += a[i];
        return r;
    }
} f, g;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            f.update(i, a[i] - a[i - 1]);
            g.update(i, max(0, a[i] - a[i - 1]));
        }
        int op, l, r, k;
        while (q--) {
            scanf("%d%d%d", &op, &l, &r);
            if (op == 1) {
                scanf("%d", &k);
                // g.update(l, k);
                ll y = f.query(l), x = f.query(l - 1);
                g.update(l, -max(y - x, 0ll));
                g.update(l, max(y - x + k, 0ll));
                if (r < n) {
                    ll x = f.query(r), y = f.query(r + 1);
                    g.update(r + 1, -max(y - x, 0ll));
                    g.update(r + 1, max(y - x - k, 0ll));
                }
                f.update(l, k); f.update(r + 1, -k);
            } else if (op == 2) {
                ll ans = f.query(l) + g.query(r) - g.query(l);
                printf("%lld\n", ans);
            }
        }
        f.clear(n); g.clear(n);
    }
    return 0;
}