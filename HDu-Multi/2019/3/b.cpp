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
const int inf = 1 << 30;
const int maxn = 100000 + 5;

vector<int> G[maxn], rG[maxn];
vector<int> dt[maxn];

namespace DomTree {
    int fa[maxn], idx[maxn], tot, ridx[maxn];
    int c[maxn], best[maxn], semi[maxn], idom[maxn];
    void clear(int n) {
        tot = 0;
        fill(c, c + n + 1, -1);
        fill(idx, idx + n + 1, 0);
        for (int i = 0; i <= n; i++) {
            dt[i].clear();
            semi[i] = best[i] = i;
        }
    }
    void dfs(int u) {
        idx[u] = ++tot; ridx[tot] = u;
        for (int& v: G[u]) {
            if (idx[v]) continue;
            fa[v] = u; dfs(v);
        }
    }
    int fix(int x) {
        if (c[x] == -1) return x;
        int &f = c[x], rt = fix(f);
        if (idx[semi[best[x]]] > idx[semi[best[f]]]) best[x] = best[f];
        return f = rt;
    }
    void build(int rt) {
        dfs(rt);
        for (int i = tot; i >= 1; i--) {
            int x = ridx[i], mn = tot + 1;
            for (int& u: rG[x]) {
                if (!idx[u]) continue;
                fix(u); mn = min(mn, idx[semi[best[u]]]);
            }
            c[x] = fa[x];
            dt[semi[x] = ridx[mn]].push_back(x);
            x = ridx[i - 1];
            for (int& u: dt[x]) {
                fix(u);
                if (semi[best[u]] != x) idom[u] = best[u];
                else idom[u] = x;
            }
            dt[x].clear();
        }
        for (int i = 2; i <= tot; i++) {
            int u = ridx[i];
            if (idom[u] != semi[u]) idom[u] = idom[idom[u]];
            dt[idom[u]].push_back(u);
        }
    }
}

int n, m, q, deg[maxn];

void dfs(int u, int f) {
    dbg(u, f);
    for (int& v: dt[u]) {
        dfs(v, u);
    }
}

namespace hld {
    int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
    void dfs(int u, int f) {
        dep[u] = dep[f] + 1; fa[u] = f; siz[u] = 1; son[u] = 0;
        int m = -1;
        for (auto& v: dt[u]) {
            if (v == f) continue;
            dfs(v, u);
            siz[u] += siz[v];
            if (siz[v] > m) son[u] = v, m = siz[v];
        }
    }
    void dfs(int u, int f, int tp) {
        top[u] = tp;
        if (!son[u]) return;
        dfs(son[u], u, tp);
        for (auto& v: dt[u]) {
            if (v == f || v == son[u]) continue;
            dfs(v, u, v);
        }
    }
    void build(int rt) {
        dfs(rt, 0); dfs(rt, 0, rt);
    }
    int qlca(int u, int v) {
        while (top[u] != top[v]){
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
}
using hld::dep;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i <= n + 1; i++) {
            deg[i] = 0;
            G[i].clear(); rG[i].clear();
        }
        for (int i = 1, u, v; i <= m; i++) {
            scanf("%d%d", &u, &v);
            G[v].push_back(u);
            rG[u].push_back(v);
            deg[u]++;
        }
        for (int i = 1; i <= n; i++) if (!deg[i]) {
            G[n + 1].push_back(i);
            rG[i].push_back(n + 1);
        }
        DomTree::clear(n + 1);
        DomTree::build(n + 1);
        hld::build(n + 1);
        scanf("%d", &q);
        while (q--) {
            int u, v; scanf("%d%d", &u, &v);
            int g = hld::qlca(u, v);
            int ans = dep[u] + dep[v] - dep[g] - 1;
            printf("%d\n", ans);
        }
    }
    return 0;
}