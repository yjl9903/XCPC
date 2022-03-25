#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <functional>
#include <assert.h>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 2000000 + 5;

int n, m, mark[maxn], vis[maxn];
ll ans, tot;
vector<PII> edge[maxn];
PII g[maxn];

int dep[maxn], fa[maxn], pre[maxn], siz[maxn];
void dfs(int u, int f) {
    vis[u] = 1;
    fa[u] = f;
    dep[u] = dep[f] + 1;
    for (auto& x: edge[u]) {
        int v = x.first;
        if (vis[v]) continue;
        if (!mark[x.second]) continue;
        // mark[x.second] = 1;
        dfs(v, u);
    }
}

int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }
ll cal(ll x) {
    return x * (x - 1) / 2;
}

struct node {
    int u, v, id;
    bool operator<(const node& b) const {
        return id > b.id;
    }
};
void kruskal() {
    priority_queue<node> pq;
    for (int i = 1; i <= m; i++) pq.push({g[i].first, g[i].second, i});
    while (!pq.empty()) {
        node x = pq.top(); pq.pop();
        int u = find(x.u), v = find(x.v);
        if (u == v) continue;
        mark[x.id] = 1;
        pre[u] = v;
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            edge[i].clear(); 
            vis[i] = 0; pre[i] = i; siz[i] = 1;
        }
        for (int i = 1; i <= m; i++) {
            mark[i] = 0;
            scanf("%d%d", &g[i].first, &g[i].second);
            edge[g[i].first].push_back({g[i].second, i});
            edge[g[i].second].push_back({g[i].first, i});
        }
        kruskal();
        for (int i = 1; i <= n; i++) if (!vis[i]) dfs(i, 0);
        for (int i = 1; i <= n; i++) pre[i] = i;
        ans = tot = 0;
        for (int i = 1; i <= m; i++) {
            if (mark[i]) {
                dbg(i, tot);
                ans ^= tot * i; continue;
            }
            int u = find(g[i].first), v = find(g[i].second);
            vector<int> vec;
            while (u != v) {
                if (dep[u] < dep[v]) swap(u, v);
                vec.push_back(u);
                u = find(fa[u]);
            }
            assert(u == v);
            tot -= cal(siz[u]);
            for (int& x: vec) {
                if (x == u) continue;
                tot -= cal(siz[x]);
                pre[x] = u;
                siz[u] += siz[x];
            }
            tot += cal(siz[u]);
            dbg(i, tot, u, siz[u]);
            ans ^= tot * i;
        }
        printf("%lld\n", ans);
    }
    return 0;
}