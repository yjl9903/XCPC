#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <assert.h>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;

inline int gi() {
    int r = 0; char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') r = r * 10 + ch - '0', ch = getchar();
    return r;
}

struct edge {
    int to, nxt, id;
} f[maxn * 2];
int head[maxn], eid;
inline void adde(int u, int v, int id) {
    f[++eid] = {v, head[u], id}; head[u] = eid;
}

vector<int> block[maxn];
int n, m, a[maxn], ans[maxn];

int tot, dfn[maxn], low[maxn], cnt, bel[maxn];
namespace Tarjan {
    edge f[maxn * 2];
    int head[maxn], eid, vis[maxn];
    inline void adde(int u, int v, int id) {
        f[++eid] = {v, head[u], id}; head[u] = eid;
    }
    int st[maxn], top;
    void dfs(int u, int eid) {
        // assert(u >= 1 && u <= n);
        // printf("%d\n", u);
        dfn[u] = low[u] = ++tot;
        st[++top] = u; vis[u] = 1;
        for (int i = head[u]; i; i = f[i].nxt) {
            int v = f[i].to, id = f[i].id;
            if (id == eid) continue;
            if (!dfn[v]) {
                dfs(v, id);
                low[u] = min(low[u], low[v]);
            } else if (vis[v]) low[u] = min(low[u], dfn[v]);
        }
        if (dfn[u] == low[u]) {
            cnt++; int t = 0;
            do {
                t = st[top--];
                bel[t] = cnt;
                vis[t] = 0;
            } while (t != u);
        }
    }
    void init() {
        cnt = tot  = top = 0;
        for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(i, 0);
        for (int i = 1; i <= n; i++) {
            block[bel[i]].push_back(i);
            for (int j = head[i]; j; j = f[j].nxt) {        
                int v = f[j].to;
                if (bel[i] != bel[v]) {
                    ::adde(bel[i], bel[v], f[j].id);
                } else ans[f[j].id] = 0;
            }
        }
    }
}

namespace DSU {
    int siz[maxn], son[maxn], ans2[maxn];
    bool vis[maxn], sk[maxn];
    int cnti[maxn], bagi[maxn], mxi, cnto[maxn], bago[maxn], mxo, allc; 
    inline void update(int x, int k) {
        bagi[cnti[x]]--; cnti[x] += k; bagi[cnti[x]]++;
        if (cnti[x] > mxi) mxi = cnti[x];
        if (bagi[mxi] == 0) mxi--;

        bago[cnto[x]]--; cnto[x] -= k; bago[cnto[x]]++;
        if (cnto[x] > mxo) mxo = cnto[x];
        if (bago[mxo] == 0) mxo--;
    }
    void add(int u, int f, int x) {
        for (auto it = block[u].begin(); it != block[u].end(); it++) {
            update(a[*it], x);
        }
        for (int i = head[u]; i; i = ::f[i].nxt) {
            int v = ::f[i].to;
            if (v == f || sk[v]) continue;
            add(v, u, x);
        }
    }
    void dfs(int u, int f, int kp) {
        vis[u] = 1; int sid = 0;
        for (int i = head[u]; i; i = ::f[i].nxt) {
            int v = ::f[i].to;
            if (v == son[u]) sid = ::f[i].id;
            if (v == f || v == son[u]) continue;
            dfs(v, u, 0);
            ans[::f[i].id] = ans2[v];
        }
        if (son[u]) dfs(son[u], u, 1), sk[son[u]] = 1;

        add(u, f, 1); 
        // for (auto it = block[u].begin(); it != block[u].end(); it++) {
        //     update(a[*it], 1);
        // }
        // for (int i = head[u]; i; i = ::f[i].nxt) {
        //     if (::f[i].to != f && ::f[i].to != son[u]) 
        //         add(::f[i].to, u, 1);
        // }

        ans2[u] = mxo + mxi - allc;
        if (son[u]) sk[son[u]] = 0, ans[sid] = ans2[son[u]];
        if (!kp) add(u, f, -1);
    }
    void dfs1(int u, int f, int kp = 1) {
        for (auto it = block[u].begin(); it != block[u].end(); it++) {
            int x = a[*it];
            if (kp) {
                bago[cnto[x]]--; cnto[x]++; bago[cnto[x]]++;
                if (cnto[x] > mxo) mxo = cnto[x];
            } else {
                bago[cnto[x]]--; cnto[x]--; bago[cnto[x]]++;
            }
        }
        siz[u] = (int)block[u].size(); son[u] = 0; int m = -1;
        for (int i = head[u]; i; i = ::f[i].nxt) {
            int v = ::f[i].to;
            if (v == f) continue;
            dfs1(v, u, kp); siz[u] += siz[v];
            if (siz[v] > m) m = siz[v], son[u] = v;
        }
    }
    inline void solve() {
        int sum = 0;
        for (int i = 1; i <= cnt; i++) if (!vis[i]) {
            mxo = mxi = 0; bago[0] = bagi[0] = n;
            dfs1(i, 0); 
            allc = mxo; sum += allc;
            dfs(i, 0, 0);
            dfs1(i, 0, 0);
        }
        for (int i = 1; i <= m; i++) ans[i] += sum;
        for (int i = 1; i <= cnt; i++) vis[i] = 0, block[i].clear();
    }
}

int main() {
    int T = gi(); 
    while (T--) {
        eid = Tarjan::eid = 0;
        n = gi(); m = gi();
        for (int i = 1;  i <= n; i++) a[i] = gi();
        for (int i = 1, u, v; i <= m; i++) {
            u = gi(); v = gi();
            Tarjan::adde(u, v, i);
            Tarjan::adde(v, u, i);
        } 
        Tarjan::init();
        DSU::solve();
        for (int i = 1; i <= m; i++) printf("%d%c", ans[i], " \n"[i == m]);
        for (int i = 1; i <= n; i++) head[i] = Tarjan::head[i] = Tarjan::vis[i] = dfn[i] = 0;
    }
    return 0;
}