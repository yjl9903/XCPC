#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

inline int lowbit(int x) {
    return x & -x;
}

int n, m, dep[maxn];
ll ans[maxn];
vector<int> edge[maxn];
vector<PII> key[maxn];

struct BIT {
    ll a[maxn];
    void update(int i, int x) {
        for (; i <= n; i += lowbit(i)) a[i] += x;
    }
    void update(int l, int r, int x) {
        update(l, x); update(r + 1, -x);
    }
    ll query(int i) {
        ll r = 0;
        for (; i; i -= lowbit(i)) r += a[i];
        return r;
    }
} f, g;

void dfs(int u, int ff) {
    dep[u] = dep[ff] + 1;
    for (auto x: key[u]) {
        int d = x.first, w = x.second;
        f.update(dep[u], dep[u] + d, w + dep[u]);
        g.update(dep[u], dep[u] + d, 1);
    }
    ans[u] = f.query(dep[u]) - 1ll * dep[u] * g.query(dep[u]);
    for (int v: edge[u]) {
        if (v == ff) continue;
        dfs(v, u);
    }
    for (auto& x: key[u]) {
        int d = x.first, w = x.second;
        f.update(dep[u], dep[u] + d, -w - dep[u]);
        g.update(dep[u], dep[u] + d, -1);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    scanf("%d", &m);
    for (int i = 1, p, d, x; i <= m; i++) {
        scanf("%d%d%d", &p, &d, &x);
        key[p].push_back({ min(d, x), x });
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) printf("%lld\n", ans[i]);
    return 0;
}