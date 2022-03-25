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
const int maxn = 200000 + 5;

int n, q, e[maxn], l[maxn], c[maxn];
vector<int> st[maxn], ed[maxn];

struct BIT {
    ll a[maxn], b[maxn];
    void clear() {
        ms(a, 0); ms(b, 0);
    }
    void update(int i, int x) {
        ll k = 1ll * i * x;
        for (; i < maxn; i += i & -i) {
            a[i] += x; b[i] += k;
        }
    }
    ll qcnt(int i) {
        ll r = 0;
        for (; i; i -= i & -i) r += a[i];
        return r;
    }
    ll qsum(int i) {
        ll r = 0;
        for (; i; i -= i & -i) r += b[i];
        return r;
    }
} f;

set<int> ev;
void add(int x) {
    if (ev.empty()) {
        ev.insert(x); return ;
    }
    auto it = ev.lower_bound(x);
    if (it != ev.end()) {
        f.update(*it - x, 1);
        if (it != ev.begin()) {
            auto it2 = it; it2--;
            f.update(x - *it2, 1);
            f.update(*it - *it2, -1);
        }
    } else {
        it--;
        f.update(x - *it, 1);
    }
    ev.insert(x);
}
void del(int x) {
    if ((int)ev.size() == 1) {
        ev.erase(x); return ;
    }
    auto it = ev.find(x);
    if (it != ev.begin()) {
        auto it2 = it; it2--;
        f.update(x - *it2, -1);
        auto it3 = it; it3++;
        if (it3 != ev.end()) {
            f.update(*it3 - x, -1);
            f.update(*it3 - *it2, 1);
        }
    } else {
        it++;
        f.update(*it - x, -1);
    }
    ev.erase(x);
}
ll query(int id) {
    if (ev.empty()) return 0;
    int first = *ev.begin();
    ll ans = min(e[id] + 1ll * first * l[id], 1ll * c[id]);
    int period = maxn;
    if (l[id]) {
        period = c[id] / l[id]; 
        if (c[id] % l[id]) period++;
    }
    ll finish = (int)ev.size() - 1 - f.qcnt(period - 1);
    ans += finish * c[id] + f.qsum(period - 1) * l[id];
    return ans;
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        ev.clear(); f.clear();
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d", e + i, l + i, c + i);
            st[i].clear(); ed[i].clear();
        }
        scanf("%d", &q);
        for (int i = 1, t, a, b; i <= q; i++) {
            scanf("%d%d%d", &t, &a, &b);
            st[a].push_back(t); 
            ed[b].push_back(t);
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int x: st[i]) add(x);
            ans += query(i);
            for (int x: ed[i]) del(x);
        }
        printf("Case #%d: %lld\n", ++kase, ans);
    }    
    return 0;
}