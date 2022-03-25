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
const int maxn = 200000 + 5;

int mpdis[maxn], mpson[maxn];
int qd(int u) {
    if (mpdis[u] != -1) return mpdis[u];
    cout << "d " << u << endl;
    int ans; cin >> ans; 
    return mpdis[u] = ans;
}
int qs(int u) {
    if (mpson[u] != -1) return mpson[u];
    cout << "s " << u << endl;
    int ans; cin >> ans;
    return mpson[u] = ans;
}
void answer(int u) {
    cout << "! " << u << endl;
}

int n;
vector<int> edge[maxn];

int dep[maxn], fa[maxn], siz[maxn], son[maxn], top[maxn];
vector<int> path[maxn];
void dfs(int u, int f) {
    dep[u] = dep[f] + 1; fa[u] = f; siz[u] = 1;
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs(v, u); siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}
void dfs(int u, int f, int tp) {
    top[u] = tp;
    path[tp].push_back(u);
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
int qlca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}
int qdis(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[qlca(u, v)];
}

int totd;
int solve(int u) {
    int d = path[u].back();
    int d1 = dep[d] - dep[u];
    // int d2 = qd(u);
    int d2 = totd;
    int d3 = qd(d);
    int dy = (d1 + d2 - d3) / 2;
    if (d2 == dy) return path[u][dy];
    int y = path[u][dy];
    totd -= dy + 1;
    return solve(qs(y));
}

int main() {
    ms(mpdis, -1); ms(mpson, -1);
    scanf("%d", &n);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    init();
    totd = qd(1);
    int r = solve(1);
    answer(r);
    return 0;
}