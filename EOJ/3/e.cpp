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
const int maxn = 100 + 5;

vector<int> edge[maxn];
int n, p, q, val[maxn];

int tot, dfn[maxn], tin[maxn], tout[maxn], dep[maxn];
void getsz(int u) {
    tin[u] = ++tot; dfn[tot] = u; 
    for (int& v: edge[u]) {
        dep[v] = dep[u] + 1;
        getsz(v);
    }
    tout[u] = tot;
}
double f[maxn][maxn], g[maxn][maxn];
void dfs(int u, int k) {
    double r = 0;
    for (int i = tin[u]; i <= tout[u]; i++) {
        r += val[i] / double(1 + dep[i] - dep[u]);
    }
    f[u][1] = r;
    for (int& v: edge[u]) {
        dfs(v, k);
        for (int i = k; i >= 0; i--) {
            for (int l = tin[v]; l <= tout[v]; l++) 
                g[u][0] += val[l] / double(1 + dep[l] - dep[u]);
            for (int j = 1; i + j <= k; j++) {
                
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2, x; i <= n; i++) {
        scanf("%d", &x);
        edge[x].push_back(i);
    }
    scanf("%d%d", &p, &q);
    for (int i = 1, id, v; i <= p; i++) {
        scanf("%d%d", &id, &v); val[id] = v;
    }
    getsz(1);

    return 0;
}