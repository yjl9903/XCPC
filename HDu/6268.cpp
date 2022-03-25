#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <bitset>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
typedef bitset<100001> BS;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 3000 + 5;

int n, m, w[maxn];
vector<int> edge[maxn];
bitset<100001> f[maxn], ans;

int vis[maxn], siz[maxn], sum, mn, rt;
void getrt(int u, int f) {
    siz[u] = 1; int t = 0;
    for (int v: edge[u]) {
        if (v == f || vis[v]) continue;
        getrt(v, u); siz[u] += siz[v];
        t = max(t, siz[v]);
    }
    t = max(t, sum - siz[u]);
    if (t < mn) mn = t, rt = u;
}
int getrt(int u) {
    sum = siz[u]; mn = 1e9; rt = 0;
    getrt(u, 0); return rt;
}

void dfs(int u, int ff) {
    f[u] = f[ff] << w[u];
    for (int v: edge[u]) {
        if (v == ff || vis[v]) continue;
        dfs(v, u);
        f[u] |= f[v];
    }
}
void solve(int u) {
    vis[u] = 1;
    f[0].reset(); f[0].set(0);
    dfs(u, 0);
    ans |= f[u];
    for (int v: edge[u]) {
        if (vis[v]) continue;
        solve(getrt(v));
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            edge[i].clear(); vis[i] = 0;
        }
        for (int i = 2, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        for (int i = 1; i <= n; i++) scanf("%d", w + i);
        ans.reset();
        siz[1] = n;
        solve(getrt(1));
        for (int i = 1; i <= m; i++) putchar('0' + ans[i]);
        puts("");
    }
    return 0;
}