#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

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

int n, m;
ll ans[maxn];

void dfs(int u, int d) {
    if (d > n) for (;;);
    for (int v: dt[u]) {
        if (ans[v]) continue;
        ans[v] = ans[u] + v;
        dfs(v, d + 1);
    }
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 0; i <= n; i++) G[i].clear(), rG[i].clear(), ans[i] = 0;
        for (int i = 1, u, v; i <= m; i++) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            rG[v].push_back(u);
        }
        DomTree::clear(n);
        DomTree::build(n);
        ans[n] = n;
        dfs(n, 1);
        for (int i = 1; i <= n; i++) printf("%d%c", ans[i], " \n"[i == n]);
    }
    return 0;
}