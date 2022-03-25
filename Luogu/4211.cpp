#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 201314;
const int inf = 1 << 30;
const int maxn = 50000 + 5;

vector<int> edge[maxn];
int n, q;

namespace hld {
    int a[maxn << 2], tag[maxn << 2];
    void pushup(int rt) {
        a[rt] = a[rt << 1] + a[rt << 1 | 1];
    }
    void pushdown(int rt, int ln, int rn) {
        if (!tag[rt]) return ;
        int t = tag[rt];
        a[rt << 1] += t * ln; a[rt << 1 | 1] += t * rn;
        tag[rt << 1] += t; tag[rt << 1 | 1] += t;
        tag[rt] = 0;
    }
    void update(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            a[rt] += r - l + 1; tag[rt]++; return ;
        }
        int m = (l + r) / 2; pushdown(rt, m - l + 1, r - m);
        if (L <= m) update(L, R, lson);
        if (R > m) update(L, R, rson);
        pushup(rt);
    }
    int query(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) return a[rt];
        int m = (l + r) / 2, ans = 0; pushdown(rt, m - l + 1, r - m);
        if (L <= m) ans += query(L, R, lson);
        if (R > m) ans += query(L, R, rson);
        return ans;
    }

    int tot, dep[maxn], siz[maxn], son[maxn], fa[maxn], top[maxn], id[maxn];
    void dfs(int u, int f) {
        dep[u] = dep[f] + 1; fa[u] = f; siz[u] = 1;
        int m = -1;
        for (int& v: edge[u]) {
            if (v == f) continue;
            dfs(v, u);
            siz[u] += siz[v];
            if (siz[v] > m) m = siz[v], son[u] = v;
        }
    }
    void dfs(int u, int f, int tp) {
        top[u] = tp; id[u] = ++tot;
        if (!son[u]) return ;
        dfs(son[u], u, tp);
        for (int& v: edge[u]) {
            if (v == f || v == son[u]) continue;
            dfs(v, u, v);
        }
    }
    void init() {
        dfs(1, 0); dfs(1, 0, 1);
    }
    void upath(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            update(id[top[u]], id[u], 1, n, 1);
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        update(id[u], id[v], 1, n, 1);
    }
    int qpath(int u, int v) {
        int ans = 0;
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            ans += query(id[top[u]], id[u], 1, n, 1);
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        ans += query(id[u], id[v], 1, n, 1);
        return ans % mod;
    }
}

struct Que {
    int r, z, id, flag;
    bool operator<(const Que& b) const {
        return r < b.r;
    }
} qu[maxn * 2];
int ans[maxn];

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 2, p; i <= n; i++) {
        scanf("%d", &p); p++; edge[p].push_back(i);
    } hld::init();
    for (int i = 1, l, r, z; i <= q; i++) {
        scanf("%d%d%d", &l, &r, &z);
        r++; z++;
        qu[2 * i - 1] = {l, z, i, -1};
        qu[2 * i] = {r, z, i, 1};
    }
    sort(qu + 1, qu + 1 + 2 * q);
    int tot = 0;
    for (int i = 1; i <= 2 * q; i++) {
        while (tot + 1 <= qu[i].r) {
            hld::upath(1, ++tot);
        }
        ans[qu[i].id] = (ans[qu[i].id] + mod + qu[i].flag * hld::qpath(1, qu[i].z)) % mod;
    }
    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}