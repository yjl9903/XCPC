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
const int maxn = 100000 + 5;

int n; ll ans = 0;
vector<int> edge[maxn];

int dep[maxn], son[maxn], top[maxn], len[maxn];
void dfs1(int u, int f) {
    len[u] = 0;
    for (int i = 0; i < (int)edge[u].size(); i++) {
        int v = edge[u][i];
        if (v == f) continue;
        dfs1(v, u);
        if (len[v] > len[son[u]]) son[u] = v, len[u] = len[v];
    }
    len[u]++;
}
int tmp[maxn * 16], *f[maxn], *g[maxn], *tot = tmp;
void make(int u, int len) {
    f[u] = tot; tot += (len + 5) * 2;
    g[u] = tot; tot += (len + 5) * 2;
}
void dfs(int u, int ff) {
    if (son[u]) {
        f[son[u]] = f[u] + 1;
        g[son[u]] = g[u] - 1;
        dfs(son[u], u);
    }
    f[u][0] = 1;
    ans += g[u][0];
    for (int i = 0; i < (int)edge[u].size(); i++) {
        int v = edge[u][i];
        if (v == ff || v == son[u]) continue;
        make(v, len[v]);
        dfs(v, u);
        for (int j = 0; j <= len[v] + 1; j++) {
            ans += f[u][j] * g[v][j + 1];
            if (j) ans += g[u][j] * f[v][j - 1];
            g[u][j] += g[v][j + 1];
            if (j) g[u][j] += f[u][j] * f[v][j - 1];
            if (j) f[u][j] += f[v][j - 1];
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v); edge[v].push_back(u);
    }
    dfs1(1, 0);
    make(1, len[1]);
    dfs(1, 0);
    cout << ans << '\n';
    return 0;
}