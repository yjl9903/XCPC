#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
// #include <cassert>
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
const int maxn = 500000 + 5;
const int block = 2000;

void assert(bool x) {
    // if (x) return ;
    // exit(0);
}

char op[20];

int n, q;
vector<int> onring, edge[maxn];

int ring[maxn], fa[maxn], vis[maxn], tot;
void dfs(int u, int f) {
    fa[u] = f; vis[u] = 1;
    for (int v: edge[u]) {
        if (v == f) continue;
        if (vis[v]) {
            if (!onring.empty()) continue;
            int x = u;
            while (x != v) {
                onring.push_back(x); x = fa[x];
            }
            onring.push_back(v);
            continue;
        }
        dfs(v, u);
    }
    vis[u] = 0;
}
int tin[maxn], st[maxn], ed[maxn], le[maxn], ri[maxn];
int st2[maxn], ed2[maxn];
void bfs(int u) {
    queue<int> q; q.push(u); tin[u] = ++tot;
    while (!q.empty()) {
        int u = q.front(), f = 0; q.pop();
        for (int v: edge[u]) {
            if (tin[v]) continue;
            if (ring[u] && ring[v]) continue;
            if (!f) st[u] = tot + 1;
            fa[v] = u;
            tin[v] = ++tot; f = 1;
            q.push(v);
        }
        if (f) ed[u] = tot;
    }
}
void dfs2(int u, int f) {
    for (int v: edge[u]) {
        if (v == f) continue;
        if (ring[u] && ring[v]) continue;
        if (st[v]) {
            if (st2[u] == 0) st2[u] = st[v], ed2[u] = ed[v];
            st2[u] = min(st[v], st2[u]);
            ed2[u] = max(ed[v], ed2[u]);
        }
        dfs2(v, u);
    }
}

struct SegTree {
    #define lson l, m, rt << 1
    #define rson m + 1, r, rt << 1 | 1
    ll a[maxn << 2], tag[maxn << 2];
    void pushup(int rt) {
        a[rt] = a[rt << 1] + a[rt << 1 | 1];
    }
    void pushdown(int rt, int ln, int rn) {
        if (!tag[rt]) return ;
        ll t = tag[rt];
        a[rt << 1] += t * ln; a[rt << 1 | 1] += t * rn;
        tag[rt << 1] += t; tag[rt << 1 | 1] += t;
        tag[rt] = 0;
    }
    void build(int l, int r, int rt) {
        tag[rt] = 0;
        if (l == r) {
            a[rt] = 0;
            return ;
        }
        int m = (l + r) / 2;
        build(lson); build(rson);
        pushup(rt);
    }
    void update(int L, int R, int x, int l, int r, int rt) {
        if (L <= l && r <= R) {
            a[rt] += 1ll * x * (r - l + 1); tag[rt] += x;
            return ;
        }
        int m = (l + r) / 2; pushdown(rt, m - l + 1, r - m);
        if (L <= m) update(L, R, x, lson);
        if (R > m) update(L, R, x, rson);
        pushup(rt);
    }
    ll query(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) return a[rt];
        int m = (l + r) / 2; pushdown(rt, m - l + 1, r - m);
        ll ans = 0;
        if (L <= m) ans += query(L, R, lson);
        if (R > m) ans += query(L, R, rson);
        return ans;
    }
} f;

void update(int u, int k, int d) {
    if (k == 0) {
        f.update(tin[u], tin[u], d, 1, n, 1);
    } else if (k == 1) {
        if (st[u]) {
            f.update(st[u], ed[u], d, 1, n, 1);
        }
        if (ring[u]) {
            f.update(tin[le[u]], tin[le[u]], d, 1, n, 1);
            f.update(tin[ri[u]], tin[ri[u]], d, 1, n, 1);
        } else {
            f.update(tin[fa[u]], tin[fa[u]], d, 1, n, 1);
        }
        f.update(tin[u], tin[u], d, 1, n, 1);
    } else if (k == 2) {
        if (st[u]) {
            f.update(st[u], ed[u], d, 1, n, 1);
        }
        if (st2[u]) {
            f.update(st2[u], ed2[u], d, 1, n, 1);
        }
        if (ring[u]) {
            int a = le[u], b = ri[u];
            update(le[u], 1, d);
            update(ri[u], 1, d);
            f.update(tin[u], tin[u], -d, 1, n, 1);
            if ((int)onring.size() == 3) {
                assert(le[u] == ri[ri[u]] && ri[u] == le[le[u]]);
                f.update(tin[le[u]], tin[le[u]], -d, 1, n, 1);
                f.update(tin[ri[u]], tin[ri[u]], -d, 1, n, 1);
            } else if ((int)onring.size() == 4) {
                assert(le[le[u]] == ri[ri[u]]);
                f.update(tin[le[le[u]]], tin[le[le[u]]], -d, 1, n, 1);
            }
        } else if (ring[fa[u]]) {
            update(fa[u], 1, d);
        } else {
            update(fa[u], 1, d);
            f.update(tin[fa[fa[u]]], tin[fa[fa[u]]], d, 1, n, 1);
        }
    }
}
ll query(int u, int k) {
    if (k == 0) {
        return f.query(tin[u], tin[u], 1, n, 1);
    } else if (k == 1) {
        ll ans = f.query(tin[u], tin[u], 1, n, 1);
        if (st[u]) {
            ans += f.query(st[u], ed[u], 1, n, 1);
        }
        if (ring[u]) {
            ans += f.query(tin[le[u]], tin[le[u]], 1, n, 1);
            ans += f.query(tin[ri[u]], tin[ri[u]], 1, n, 1);
        } else {
            ans += f.query(tin[fa[u]], tin[fa[u]], 1, n, 1);
        }
        return ans;
    } else if (k == 2) {
        ll ans = 0;
        if (st[u]) {
            ans += f.query(st[u], ed[u], 1, n, 1);
        }
        if (st2[u]) {
            ans += f.query(st2[u], ed2[u], 1, n, 1);
        }
        if (ring[u]) {
            int a = le[u], b = ri[u];
            ans += query(le[u], 1) + query(ri[u], 1) - f.query(tin[u], tin[u], 1, n, 1);
            if ((int)onring.size() == 3) {
                assert(le[u] == ri[ri[u]] && ri[u] == le[le[u]]);
                ans -= f.query(tin[le[u]], tin[le[u]], 1, n, 1);
                ans -= f.query(tin[ri[u]], tin[ri[u]], 1, n, 1);
            } else if ((int)onring.size() == 4) {
                assert(le[le[u]] == ri[ri[u]]);
                ans -= f.query(tin[le[le[u]]], tin[le[le[u]]], 1, n, 1);
            }
        } else if (ring[fa[u]]) {
            ans += query(fa[u], 1);
        } else {
            ans += query(fa[u], 1);
            ans += f.query(tin[fa[fa[u]]], tin[fa[fa[u]]], 1, n, 1);
        }
        return ans;
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        tot = 0;
        scanf("%d", &n);
        for (int i = 1, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v); edge[v].push_back(u);
        } 
        f.build(1, n, 1);
        onring.clear(); dfs(1, 0);
        assert((int)onring.size() >= 3);
        for (int i = 0; i < (int)onring.size(); i++) {
            int x = onring[i];
            ring[x] = 1;
            if (i == 0) {
                le[x] = onring.back();
                ri[x] = onring[i + 1];
            } else if (i + 1 == (int)onring.size()) {
                le[x] = onring[i - 1];
                ri[x] = onring.front();
            } else {
                le[x] = onring[i - 1];
                ri[x] = onring[i + 1];
            }
        }
        for (int x: onring) {
            bfs(x); dfs2(x, 0);
        }
        assert(tot == n);
        for (int i = 1; i <= n; i++) {
            // dbg(i, tin[i], st[i], ed[i]);
            // dbg(st2[i], ed2[i]);
            assert(tin[i] >= 1 && tin[i] <= n);
            if (ring[i]) {
                assert(ri[i] >= 1 && ri[i] <= n);
                assert(le[i] >= 1 && le[i] <= n);
            }
        }
        int u, k, d;
        scanf("%d", &q);
        while (q--) {
            scanf("%s%d%d", op, &u, &k);
            if (op[0] == 'M') {
                scanf("%d", &d);
                update(u, k, d);
                // dbg(u, k, d);
                // for (int i = 1; i <= n; i++) {
                //     dbg(i, f.query(tin[i], tin[i], 1, n, 1));
                // }
            } else if (op[0] == 'Q') {
                printf("%lld\n", query(u, k));
            }
        }
        for (int i = 1; i <= n; i++) {
            edge[i].clear();
            fa[i] = ring[i] = 0;
            st2[i] = ed2[i] = 0;
            tin[i] = st[i] = ed[i] = le[i] = ri[i] = 0;
        }
    }
    return 0;
}