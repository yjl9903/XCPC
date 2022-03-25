#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,ll> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

struct Edge {
    int u, v; ll w;
} eg[maxn];

vector<PII> edge[maxn]; ll mw;
int n, q, tin[maxn], tout[maxn], rid[maxn], tot;

namespace hld {
    struct BIT {
        ll a[maxn];
        inline int lowbit(int x) {
            return x & -x;
        }
        inline void update(int i, ll x) {
            for (; i <= n; i += lowbit(i)) a[i] += x;
        }
        inline void update(int l, int r, ll x) {
            update(l, x); update(r + 1, -x);
        }
        inline ll query(int i) {
            ll r = 0;
            for (; i; i -= lowbit(i)) r += a[i];
            return r;
        }
    } g;

    int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
    void dfs(int u, int f) {
        tin[u] = ++tot; rid[tot] = u;
        dep[u] = dep[f] + 1; fa[u] = f; siz[u] = 1; son[u] = 0;
        int m = -1;
        for (auto& x: edge[u]) {
            int v = x.first;
            if (v == f) continue;
            dfs(v, u);
            g.update(tin[v], tout[v], x.second);
            siz[u] += siz[v];
            if (siz[v] > m) son[u] = v, m = siz[v];
        }
        tout[u] = tot;
    }
    void dfs(int u, int f, int tp) {
        top[u] = tp;
        if (!son[u]) return;
        dfs(son[u], u, tp); // !
        for (auto& x: edge[u]) {
            int v = x.first;
            if (v == f || v == son[u]) continue; // !
            dfs(v, u, v);
        }
    }
    void build() {
        dfs(1, 0); dfs(1, 0, 1);
    }
    int qlca(int u, int v) {
        while (top[u] != top[v]){
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
    ll qdis(int u, int v) {
        ll r = g.query(tin[u]) + g.query(tin[v]);
        int l = qlca(u, v);
        return r - 2ll * g.query(tin[l]);
    }
}
using hld::qdis;

struct Node {
    int u, v; ll d;
} a[maxn << 2];
void pushup(int rt) {
    if (a[rt << 1].d > a[rt << 1 | 1].d) {
        a[rt] = a[rt << 1];
    } else {
        a[rt] = a[rt << 1 | 1];
    }
    int x = a[rt << 1].u, y = a[rt << 1].v;
    int u = a[rt << 1 | 1].u, v = a[rt << 1 | 1].v;
    ll tot;
    if ((tot = qdis(x, u)) > a[rt].d) a[rt] = (Node){ x, u, tot };
    if ((tot = qdis(x, v)) > a[rt].d) a[rt] = (Node){ x, v, tot };
    if ((tot = qdis(y, u)) > a[rt].d) a[rt] = (Node){ y, u, tot };
    if ((tot = qdis(y, v)) > a[rt].d) a[rt] = (Node){ y, v, tot };
}
void build(int l = 1, int r = n, int rt = 1) {
    if (l == r) {
        int u = rid[l];
        a[rt] = (Node){ u, u, 0 };
        return ;
    }
    int m = (l + r) / 2;
    build(lson);  build(rson);
    pushup(rt);
}
void update(int L, int R, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) return ;
    int m = (l + r) / 2;
    if (L <= m) update(L, R, lson);
    if (R > m) update(L, R, rson);
    pushup(rt);
}

int main() {
    scanf("%d%d%lld", &n, &q, &mw);
    for (int i = 1; i < n; i++) {
        scanf("%d%d%lld", &eg[i].u, &eg[i].v, &eg[i].w);
        edge[eg[i].u].push_back({ eg[i].v, eg[i].w });
        edge[eg[i].v].push_back({ eg[i].u, eg[i].w });
    }
    hld::build(); build();
    ll last = 0, w;
    for (int i = 1, e; i <= q; i++) {
        scanf("%d%lld", &e, &w);
        e = (e + last) % (n - 1) + 1;
        w = (w + last) % mw;
        int u = eg[e].u, v = eg[e].v, ww = eg[e].w;
        if (hld::fa[v] != u) swap(u, v);
        hld::g.update(tin[v], tout[v], w - ww);
        eg[e].w = w;
        update(tin[v], tout[v]);
        printf("%lld\n", last = a[1].d);
    }
    return 0;
}