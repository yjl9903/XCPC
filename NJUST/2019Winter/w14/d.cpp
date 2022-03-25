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
const int maxn = 1000000 + 5;

vector<int> edge[maxn];
int n, k, tr[maxn], in[maxn], out[maxn], fa[maxn], dep[maxn], tot, vis[maxn];

inline int lowbit(int i) { return i & -i; }
inline void update(int i, int x) {
    while (i < maxn) tr[i] += x, i += lowbit(i);
}
inline int query(int i) {
    int r = 0; while (i > 0) r += tr[i], i -= lowbit(i); return r;
}

void dfs(int u, int f) {
    in[u] = ++tot; fa[u] = f;
    for (int& v: edge[u]) {
        if (v == f) continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
    out[u] = tot;
}

int main() {
    scanf("%d%d", &n, &k); k = n - k;
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v); edge[v].push_back(u);
    }
    dep[n] = 1; dfs(n, 0); int now = 0;
    for (int i = n; i >= 1; i--) {
        if (vis[i]) continue;
        if (dep[i] - query(in[i]) + now > k) continue;
        for (int x = i; x && vis[x] == 0; x = fa[x]) {
            now++; vis[x] = 1; 
            update(in[x], 1); update(out[x] + 1, -1);
        }
    }
    for (int i = 1; i <= n; i++) if (!vis[i]) printf("%d ", i);
    return 0;
}