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
const int maxn = 5000 + 10;

int n; ll ans;
struct Edge {
    int to, nxt;
} eg[maxn * 2];
int head[maxn], tot;
void add(int u, int v) {
    eg[++tot] = { v, head[u] }; head[u] = tot;
}

int f[maxn][maxn];
int g[maxn][maxn];

void dfs(int u, int ff) {
    f[u][0] = 1;
    for (int i = head[u]; i; i = eg[i].nxt) {
        int v = eg[i].to;
        if (v == ff) continue;
        dfs(v, u);
        for (int j = 0; j <= n; j++) {
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
        add(u, v); add(v, u);
    }
    dfs(1, 0);
    cout << ans;
    return 0;
}