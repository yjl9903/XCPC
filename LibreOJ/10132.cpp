#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

vector<PII> edge[maxn];
int n, q, dfn[maxn], id[maxn], tot;

namespace LCA {
    int fa[maxn][20], dep[maxn];
    ll dis[maxn];
    void dfs(int u, int f) {
        dfn[u] = ++tot; id[tot] = u;
        fa[u][0] = f; dep[u] = dep[f] + 1;
        for (auto& x: edge[u]) {
            int v = x.first;
            if (v == f) continue;
            dis[v] = dis[u] + x.second;
            dfs(v, u);
        }
    }
    void init() {
        dfs(1, 0);
        for (int j = 1; j < 20; j++) for (int i = 1; i <= n; i++) 
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
    }
    int qlca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        int tmp = dep[u] - dep[v];
        for (int i = 0; tmp; i++, tmp >>= 1) if (tmp & 1) u = fa[u][i];
        if (u == v) return u;
        for (int i = 19; i >= 0; i--) if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
        return fa[u][0];
    }
    ll qdis(int u, int v) {
        return dis[u] + dis[v] - 2ll * dis[qlca(u, v)];
    }
}

int main(){
    scanf("%d", &n);
    for (int i = 2, u, v, w; i <= n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        edge[u].push_back({v, w});
        edge[v].push_back({u, w});
    } LCA::init();
    scanf("%d", &q);
    char op[3]; int x; ll ans = 0; set<int> st;
    while (q--) {
        scanf("%s", op);
        if (op[0] == '+') {
            scanf("%d", &x);
            st.insert(dfn[x]);
            auto it = st.find(dfn[x]);
            auto l = it, r = it; r++;
            if (l == st.begin()) l = --st.end();
            else l--;
            if (r == st.end()) r = st.begin();
            ans += LCA::qdis(id[*l], x) + LCA::qdis(x, id[*r]) - LCA::qdis(id[*l], id[*r]);
        }
        if (op[0] == '-') {
            scanf("%d", &x);
            auto it = st.find(dfn[x]);
            auto l = it, r = it; r++;
            if (l == st.begin()) l = --st.end();
            else l--;
            if (r == st.end()) r = st.begin();
            ans -= LCA::qdis(id[*l], x) + LCA::qdis(x, id[*r]) - LCA::qdis(id[*l], id[*r]);
            st.erase(it);
        }
        if (op[0] == '?') {
            printf("%lld\n", ans / 2);
        }
    }
    return 0;
}