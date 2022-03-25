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
const int maxn = 300000 + 5;

int n, m;
vector<int> edge[maxn];

int dep[maxn], son[maxn], top[maxn], len[maxn], maxd[maxn], fa[maxn][20];
void dfs(int u, int f) {
    maxd[u] = dep[u] = dep[f] + 1;
    fa[u][0] = f; son[u] = 0;
    for (int i = 1; i < 20; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int v: edge[u]) {
        if (v == f) continue;
        dfs(v, u);
        if (maxd[v] > maxd[son[u]]) son[u] = v, maxd[u] = maxd[v];
    }
}
void dfs(int u, int f, int tp, int l) {
    top[u] = tp; len[u] = l;
    if (son[u]) {
        dfs(son[u], u, tp, l + 1);
        len[u] = len[son[u]];
    }
    for (int& v: edge[u]) {
        if (v == f || v == son[u]) continue;
        dfs(v, u, v, 1);
    }
}
bool vis[maxn]; int highbit[maxn];
vector<int> up[maxn], dwn[maxn];
void init() {
    dfs(1, 0); dfs(1, 0, 1, 1);
    for (int i = 1; i <= n; i++) {
        int tp = top[i];
        if (!vis[tp]) {
            vis[tp] = 1;
            int l = 0, now = tp;
            while (l < len[tp] && now) {
                now = fa[now][0];
                l++; up[tp].push_back(now);
            }
            l = 0, now = tp;
            while (l < len[tp]) {
                now = son[now];
                l++; dwn[tp].push_back(now);
            }
        }
    }
    int mx = 1;
    for (int i = 1; i <= n; i++) {
        if (i >> mx & 1) mx++;
        highbit[i] = mx - 1;
    }
}
int qkth(int u, int k) {
    if (k > dep[u]) return 0;
    if (k == 0) return u;
    u = fa[u][highbit[k]]; k -= 1 << highbit[k];
    if (k == 0) return u;
    if (dep[u] - dep[top[u]] == k) return top[u];
    if (dep[u] - dep[top[u]] > k) return dwn[top[u]][dep[u] - dep[top[u]] - k - 1];
    return up[top[u]][k - (dep[u] - dep[top[u]]) - 1];
}

int main() {
    scanf("%d", &n);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v); edge[v].push_back(u);
    } init();
    scanf("%d", &m);
    int u, k, lastans = 0;
    while (m--) {
        scanf("%d%d", &u, &k);
        u ^= lastans; k ^= lastans;
        printf("%d\n", lastans = qkth(u, k));
    }
    return 0;
}