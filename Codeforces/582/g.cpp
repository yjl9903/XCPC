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

struct Edge {
    int u, v, w;
    bool operator<(const Edge& b) const {
        return w < b.w;
    }
} g[maxn];

int n, m, pre[maxn], siz[maxn];
ll ans[maxn];

int find(int x) {
    return x == pre[x] ? x : pre[x] = find(pre[x]);
}
ll cal(int x) {
    return 1ll * x * (x - 1) / 2;
}

int main() {
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= n; i++) pre[i] = i, siz[i] = 1;
    for (int i = 1; i < n; i++) {
        scanf("%d%d%d", &g[i].u, &g[i].v, &g[i].w);
    }
    sort(g + 1, g + n);
    vector<PII> que;
    for (int i = 1, x; i <= m; i++) {
        scanf("%d", &x); que.push_back({x, i});
    }
    sort(que.begin(), que.end());
    ll sum = 0, p = 0;
    for (auto q: que) {
        while (p + 1 < n && g[p + 1].w <= q.first) {
            p++; int u = find(g[p].u), v = find(g[p].v);
            sum -= cal(siz[u]);
            sum -= cal(siz[v]);
            pre[v] = u; siz[u] += siz[v];
            sum += cal(siz[u]);
        }
        ans[q.second] = sum;
    }
    for (int i = 1; i <= m; i++) printf("%lld ", ans[i]);
    return 0;
}