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
typedef pair<ll,int> PLI;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

struct BIT {
    static const int R = 1 << 21;
    int a[R];
    inline int lowbit(int x) { return x & -x; }
    void insert(int i) {
        for (; i < R; i += lowbit(i)) a[i]++;
    }
    int findx(int p, int rk) {
        // if (p > R) return -1;
        if (p & 1) {
            // if (p + (a[p] < rk) > R) return -1;
            return p + (a[p] < rk);
        } else {
            if (rk > a[p]) return findx(p + lowbit(p) / 2, rk - a[p]);
            else return findx(p - lowbit(p) / 2, rk);
        }
    }
    int findx(int rk) {
        return findx(R >> 1, rk);
    }
} f;

int n, m, q, b[maxn], ans[maxn];
PII a[maxn];
PLI que[maxn];

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; i++) a[i].second = i;
    for (int i = 1; i <= n; i++) {
        scanf("%d", b + i);
        a[b[i]].first++;
    }
    sort(a + 1, a + 1 + m);
    for (int i = 1; i <= q; i++) scanf("%I64d", &que[i].first), que[i].second = i;
    sort(que + 1, que + 1 + q);
    
    int p = 0;
    ll last = 0, nxt = n;
    for (int i = 1; i <= q; i++) {
        ll tot = que[i].first;
        while (tot > nxt && p < m) {
            int x = a[p].first, st = p + 1;
            while (p < m && a[st].first == a[p + 1].first) {
                f.insert(a[++p].second);
            }
            last = nxt;
            if (p < m) nxt += 1ll * p * (a[p + 1].first - a[p].first);
        }
        tot -= last + 1;
        ans[que[i].second] = f.findx(tot % p + 1);
    }
    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}