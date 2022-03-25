#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <functional>
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
const int inf = 1 << 30;
const int maxn = 300000 + 5;

int n, t, gl[maxn], gr[maxn], v[maxn], p[maxn];
ll a[maxn];

struct SegTree {
    #define lson l, m, rt << 1
    #define rson m + 1, r, rt << 1 | 1
    function<ll(ll,ll)> merge;
    ll b[maxn], a[maxn << 2];
    int tag[maxn << 2];
    void build(int l = 1, int r = n, int rt = 1) {
        if (l == r) {
            a[rt] = b[l]; return ;
        }
        int m = (l + r) / 2;
        build(lson); build(rson);
        a[rt] = merge(a[rt << 1], a[rt << 1 | 1]);
    }
    void push(int rt, int x) {
        a[rt] += x; tag[rt] += x;
    }
    void pushdown(int rt) {
        if (!tag[rt]) return ;
        push(rt << 1, tag[rt]);
        push(rt << 1 | 1, tag[rt]);
        tag[rt] = 0;
    }
    void update(int L, int R, int l = 1, int r = n, int rt = 1) {
        if (L <= l && r <= R) {
            push(rt, 1); return ;
        }
        int m = (l + r) / 2; pushdown(rt);
        if (L <= m) update(L, R, lson);
        if (R > m) update(L, R, rson);
        a[rt] = merge(a[rt << 1], a[rt << 1 | 1]);
    }
    ll query(int L, int R, int l = 1, int r = n, int rt = 1) {
        if (L <= l && r <= R) return a[rt];
        int m = (l + r) / 2; pushdown(rt);
        if (R <= m) return query(L, R, lson);
        if (L > m) return query(L, R, rson);
        return merge(query(L, R, lson), query(L, R, rson));
    }
} f, g;

int main() {
    f.merge = [](ll a, ll b) { return max(a, b); };
    g.merge = [](ll a, ll b) { return min(a, b); };
    scanf("%d%d", &n, &t);
    for (int i = 1; i <= t; i++) {
        scanf("%lld", a + i);
        a[i] += a[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", gl + i, gr + i, v + i);
        p[i] = i;
        f.b[i] = -a[gr[i]];
        g.b[i] = -a[gl[i] - 1];
    }
    f.build(); g.build();
    sort(p + 1, p + 1 + n, [&](int a, int b) {
        return v[a] > v[b];
    });
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int x = p[i];
        if (f.query(x, n) + 1 <= g.query(1, x)) {
            ans += v[x];
            f.update(x, n);
            if (x < n) g.update(x + 1, n);
        }
    }
    cout << ans;
    return 0;
}