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
const int maxn = 1000000 + 5;

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
ll ans = 0; set<int> st;
void insert(int x) {
    st.insert(dfn[x]);
    auto it = st.find(dfn[x]);
    auto l = it, r = it; r++;
    if (l == st.begin()) l = --st.end();
    else l--;
    if (r == st.end()) r = st.begin();
    ans += LCA::qdis(id[*l], x) + LCA::qdis(x, id[*r]) - LCA::qdis(id[*l], id[*r]);
}
void del(int x) {
    auto it = st.find(dfn[x]);
    auto l = it, r = it; r++;
    if (l == st.begin()) l = --st.end();
    else l--;
    if (r == st.end()) r = st.begin();
    ans -= LCA::qdis(id[*l], x) + LCA::qdis(x, id[*r]) - LCA::qdis(id[*l], id[*r]);
    st.erase(it);
}

int k;

int main(){
    scanf("%d%d", &n, &k);
    for (int i = 2, u, v, w; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back({v, 1});
        edge[v].push_back({u, 1});
    } LCA::init();
    // puts("ha");
    insert(n);
    set<int> res; res.insert(n);
    for (int i = n - 1; i >= 1; i--) {
        insert(i);
        if (ans / 2 > n - k - 1) {
            del(i);
        } else {
            res.insert(i);
        }
    }
    // for (int x: res) cout << x << endl;
    for (int i = 1; i <= n; i++) if (!res.count(i)) printf("%d ", i);
    return 0;
}