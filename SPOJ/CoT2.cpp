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
const int maxn = 1000000 + 5;
const int sz = 300;

int n, m, a[maxn], ans[maxn];
vector<int> edge[maxn];

int dfn[maxn],tot;
int stk[maxn], tp, bcnt, bel[maxn], key[maxn];
int dep[maxn], fa[maxn], siz[maxn], son[maxn], top[maxn];
void dfs(int u, int f) {
    dfn[u] = ++tot;
    siz[u] = 1; dep[u] = dep[f] + 1; fa[u] = f; 
    int m = -1, bot = tp;
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs(v, u);
        siz[u] += siz[v];
        if (siz[v] > m) m = siz[v], son[u] = v; 
        if (tp - bot >= sz) {
            bcnt++; key[bcnt] = u;
            while (tp != bot) {
                bel[stk[tp--]] = bcnt;
            }
        }
    }
    stk[++tp] = u;
}
void dfs(int u, int f, int tp) {
    top[u] = tp;
    if (!son[u]) return ;
    dfs(son[u], u, tp);
    for (int& v: edge[u]) {
        if (v == f || v == son[u]) continue;
        dfs(v, u, v);
    }
}
int qlca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}
void init() {
    dfs(1, 0);
    while (tp) bel[stk[tp--]] = bcnt;
    dfs(1, 0, 1);
}

struct Que {
    int u, v, id;
    bool operator<(const Que& b) const {
        if (bel[u] == bel[b.u]) return dfn[v] < dfn[b.v];
        return bel[u] < bel[b.u];
    }
} q[maxn];

int vis[maxn], bag[maxn], res;
void add(int x) {
    bag[x]++; if (bag[x] == 1) res++;
}
void del(int x) {
    bag[x]--; if (bag[x] == 0) res--;
}
void update(int u) {
    if (!vis[u]) {
        add(a[u]);
    } else {
        del(a[u]);
    }
    vis[u] ^= 1;
}
void move(int u, int v) {
    int g = qlca(u, v);
    for (int tot = u; tot != g; tot = fa[tot]) {
        update(tot);
    }
    for (int tot = v; tot != g; tot = fa[tot]) {
        update(tot);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    vector<int> lsh;
    for (int i = 1; i <= n; i++) scanf("%d", a + i), lsh.push_back(a[i]);
    sort(lsh.begin(), lsh.end()); lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    for (int i = 1; i <= n; i++) a[i] = lower_bound(lsh.begin(), lsh.end(), a[i]) - lsh.begin() + 1;
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v); edge[v].push_back(u);
    }
    init();
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &q[i].u, &q[i].v);
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m);
    int u = 1, v = 1;
    for (int i = 1; i <= m; i++) {
        move(u, q[i].u);
        move(v, q[i].v);
        u = q[i].u; v = q[i].v;
        int g = qlca(u, v);
        update(g);
        ans[q[i].id] = res;
        update(g);
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}