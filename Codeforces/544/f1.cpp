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
const int maxn = 200000 + 5;

vector<int> edge[maxn];
int n, m, deg[maxn];

vector<PII> ans; int vis[maxn];
void dfs(int u) {
    vis[u] = 1;
    for (int& v: edge[u]) {
        if (vis[v]) continue;
        ans.push_back({u, v});
        dfs(v);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
        deg[u]++; deg[v]++;
    }
    int mx = deg[1], p = 1;
    for (int i = 1; i <= n; i++) if (deg[i] > mx) mx = deg[i], p = i;
    vis[p] = 1;
    for (int v: edge[p]) {
        vis[v] = 1;
        ans.push_back({p, v});
    }
    for (int& v: edge[p]) {
        dfs(v);
    }
    for (auto& x: ans) printf("%d %d\n", x.first, x.second);
    return 0;
}