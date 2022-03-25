#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const ll inf = 1ll << 60;
const int maxn = 100000 + 5;

int n, x[maxn], y[maxn], a[maxn], b[maxn];

namespace SegTree {
    #define lson l, m, rt << 1
    #define rson m + 1, r, rt << 1 | 1
    ll a[maxn << 2], tag[maxn << 2];
    void push(int rt, ll x) {
        a[rt] += x; tag[rt] += x;
    }
    void pushdown(int rt) {
        if (!tag[rt]) return ;
        push(rt << 1, tag[rt]); push(rt << 1 | 1, tag[rt]);
        tag[rt] = 0;
    }
    void pushup(int rt) {
        a[rt] = max(a[rt << 1], a[rt << 1 | 1]);
    }
    void build(int l, int r, int rt) {
        tag[rt] = 0;
        if (l == r) {
            a[rt] = -inf; if (l <= 1) a[rt] = 0;
            return ;
        }
        int m = (l + r) / 2;
        build(lson); build(rson);
        pushup(rt);
    }
    void update(int L, int R, ll x, int l, int r, int rt) {
        if (L <= l && r <= R) {
            push(rt, x); return ;
        }
        int m = (l + r) / 2; pushdown(rt);
        if (L <= m) update(L, R, x, lson);
        if (R > m) update(L, R, x, rson);
        pushup(rt);
    }
    void update(int i, ll x, int l, int r, int rt) {
        if (l == r) {
            a[rt] = max(a[rt], x); return ;
        }
        int m = (l + r) / 2; pushdown(rt);
        if (i <= m) update(i, x, lson);
        else update(i, x, rson);
        pushup(rt);
    }
    ll query(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) return a[rt];
        int m = (l + r) / 2; pushdown(rt); 
        ll ans = -inf;
        if (L <= m) ans = query(L, R, lson);
        if (R > m) ans = max(ans, query(L, R, rson));
        return ans;
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        vector<int> lsh, ord(n);
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d%d", x + i, y + i, a + i, b + i);
            // ans += a[i]; b[i] -= a[i];
            lsh.push_back(y[i]); ord[i - 1] = i;
        }
        lsh.push_back(-1);
        sort(lsh.begin(), lsh.end());
        lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
        for (int i = 1; i <= n; i++) 
            y[i] = lower_bound(lsh.begin(), lsh.end(), y[i]) - lsh.begin() + 1;
        sort(ord.begin(), ord.end(), [&](int a, int b) {
            if (x[a] == x[b]) return y[a] > y[b];
            return x[a] < x[b];
        });
        int m = (int)lsh.size() + 1;
        SegTree::build(1, m, 1);
        for (int i: ord) {
            ll pre = SegTree::query(1, y[i], 1, m, 1);
            SegTree::update(y[i], pre + b[i], 1, m, 1);
            SegTree::update(y[i] + 1, m, b[i], 1, m, 1);
            SegTree::update(1, y[i] - 1, a[i], 1, m, 1);
        }
        printf("%lld\n", SegTree::query(1, m, 1, m, 1));
        // for (int i: ord) {
        //     SegTree::update(y[i], m, b[i], 1, m, 1);
        //     ll od = SegTree::query(y[i], y[i], 1, m, 1);
        //     ll nw = SegTree::query(1, y[i] - 1, 1, m, 1) + b[i];
        //     if (nw > od) SegTree::update(y[i], y[i], nw - od, 1, m, 1);
        // }
        // printf("%lld\n", ans + SegTree::query(1, m, 1, m, 1));
    }
    return 0;
}