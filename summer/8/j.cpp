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
    if (x) return ;
    int z = 1, y = 0;
    printf("%d\n", z / y);
    exit(0);
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
int tin[maxn], tin2[maxn], st[maxn], ed[maxn], le[maxn], ri[maxn];
int st2[maxn], ed2[maxn];
void bfs(int u) {
    queue<int> q; q.push(u); tin[u] = ++tot;
    while (!q.empty()) {
        int u = q.front(), f = 0; q.pop();
        for (int v: edge[u]) {
            if (tin[v]) continue;
            if (ring[u] && ring[v]) continue;
            tin[v] = ++tot; 
            if (st[u] == 0) st[u] = tot;
            ed[u] = tot;
            q.push(v);
        }
    }
}
void dfs2(int u, int f) {
    fa[u] = f;
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

struct Fenwick {
    ll c[maxn], s[maxn];
    inline void build(int n) {
        for (int i = 1; i <= n + 5; i++) c[i] = s[i] = 0;
    }
    inline int lowbit(int i) { return i & -i; }
    inline void update(int i, int x) {
        ll y = 1ll * i * x;
        for (; i <= n + 5; i += lowbit(i)) {
            c[i] += x; s[i] += y;
        }
    }
    inline void update(int l, int r, int x) {
        assert(1 <= l && l <= r && r <= n);
        update(l, x); update(r + 1, -x);
    }
    inline ll query(ll* a, int i) {
        ll r = 0;
        for (; i; i -= lowbit(i)) r += a[i];
        return r;
    }
    inline ll query(int l, int r) {
        assert(1 <= l && l <= r && r <= n);
        return (r - l + 1) * query(c, l - 1) + (r + 1) * (query(c, r) - query(c, l - 1)) 
                - query(s, r) + query(s, l - 1);
    }
} f;

void update(int u, int k, int d) {
    if (k == 0) {
        f.update(tin[u], tin[u], d);
    } else if (k == 1) {
        if (st[u]) {
            f.update(st[u], ed[u], d);
        }
        if (ring[u]) {
            f.update(tin[le[u]], tin[le[u]], d);
            f.update(tin[ri[u]], tin[ri[u]], d);
        } else {
            f.update(tin[fa[u]], tin[fa[u]], d);
        }
        f.update(tin[u], tin[u], d);
    } else if (k == 2) {
        if (st[u]) {
            f.update(st[u], ed[u], d);
        }
        if (st2[u]) {
            f.update(st2[u], ed2[u], d);
        }
        if (ring[u]) {
            int a = le[u], b = ri[u];
            update(le[u], 1, d);
            update(ri[u], 1, d);
            f.update(tin[u], tin[u], -d);
            if ((int)onring.size() == 3) {
                // assert(le[u] == ri[ri[u]] && ri[u] == le[le[u]]);
                f.update(tin[le[u]], tin[le[u]], -d);
                f.update(tin[ri[u]], tin[ri[u]], -d);
            } else if ((int)onring.size() == 4) {
                // assert(le[le[u]] == ri[ri[u]]);
                f.update(tin[le[le[u]]], tin[le[le[u]]], -d);
            }
        } else if (ring[fa[u]]) {
            update(fa[u], 1, d);
        } else {
            update(fa[u], 1, d);
            f.update(tin[fa[fa[u]]], tin[fa[fa[u]]], d);
        }
    }
}
ll query(int u, int k) {
    if (k == 0) {
        return f.query(tin[u], tin[u]);
    } else if (k == 1) {
        ll ans = f.query(tin[u], tin[u]);
        if (st[u]) {
            ans += f.query(st[u], ed[u]);
        }
        if (ring[u]) {
            dbg(le[u], ri[u]);
            ans += f.query(tin[le[u]], tin[le[u]]);
            ans += f.query(tin[ri[u]], tin[ri[u]]);
        } else {
            ans += f.query(tin[fa[u]], tin[fa[u]]);
        }
        return ans;
    } else if (k == 2) {
        ll ans = 0;
        if (st[u]) {
            dbg(st[u], ed[u]);
            ans += f.query(st[u], ed[u]);
        }
        if (st2[u]) {
            ans += f.query(st2[u], ed2[u]);
        }
        if (ring[u]) {
            int a = le[u], b = ri[u];
            ans += query(le[u], 1) + query(ri[u], 1) - f.query(tin[u], tin[u]);
            if ((int)onring.size() == 3) {
                // assert(le[u] == ri[ri[u]] && ri[u] == le[le[u]]);
                ans -= f.query(tin[le[u]], tin[le[u]]);
                ans -= f.query(tin[ri[u]], tin[ri[u]]);
            } else if ((int)onring.size() == 4) {
                // assert(le[le[u]] == ri[ri[u]]);
                ans -= f.query(tin[le[le[u]]], tin[le[le[u]]]);
            }
        } else if (ring[fa[u]]) {
            ans += query(fa[u], 1);
        } else {
            ans += query(fa[u], 1);
            ans += f.query(tin[fa[fa[u]]], tin[fa[fa[u]]]);
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
        f.build(n);
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
            bfs(x); 
        }
        for (int x: onring) {
            dbg(x);
            dfs2(x, 0);
        }
        assert(tot == n);
        for (int i = 1; i <= n; i++) {
            dbg(i, fa[i]);
            // dbg(i, tin[i], st[i], ed[i]);
            // dbg(st2[i], ed2[i]);
            // assert(tin[i] >= 1 && tin[i] <= n);
            // if (ring[i]) {
            //     assert(ri[i] >= 1 && ri[i] <= n);
            //     assert(le[i] >= 1 && le[i] <= n);
            // }
        }
        int u, k, d;
        scanf("%d", &q);
        while (q--) {
            scanf("%s%d%d", op, &u, &k);
            dbg(op, u, k);
            if (op[0] == 'M') {
                scanf("%d", &d);
                update(u, k, d);
            } else if (op[0] == 'Q') {
                printf("%lld\n", query(u, k));
            }
        }
        for (int i = 1; i <= n; i++) {
            edge[i].clear();
            fa[i] = ring[i] = 0;
            st2[i] = ed2[i] = tin2[i] = 0;
            tin[i] = st[i] = ed[i] = le[i] = ri[i] = 0;
        }
    }
    return 0;
}