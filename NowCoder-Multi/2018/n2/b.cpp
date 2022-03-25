#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const ll inf = 1ll << 62;
const int maxn = 100000 + 5;

struct DSU {
    int pre[maxn];
    void init(int n) {
        for (int i = 1; i <= n; i++) pre[i] = i;
    }
    int find(int x) {
        return x == pre[x] ? x : pre[x] = find(pre[x]);
    }
    int join(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return 0;
        pre[x] = y;
        return 1;
    }
} f;

vector<int> edge[maxn];
int n, p[maxn], d[maxn], fa[maxn];

vector<int> onring;
int ring[maxn], vis[maxn], ok[maxn];
void getring(int u) {
    vis[u] = ok[u] = 1;
    for (int v: edge[u]) {
        if (vis[v]) {
            if (!onring.empty()) continue;
            int x = u;
            while (x != v) onring.push_back(x), x = fa[x];
            onring.push_back(v);
        }
        getring(v);
    }
    vis[u] = 0;
}
ll dp[maxn][2];
// dp[u][0] -> get all the things
// dp[u][1] -> get all the things and buy u
void dfs(int u) {
    ll sum = 0;
    for (int v: edge[u]) {
        if (ring[u] && ring[v]) continue;
        dfs(v);
        sum += dp[v][0];
    }
    dp[u][1] = sum + p[u];
    dp[u][0] = p[u] - d[u] + sum;
    for (int v: edge[u]) {
        if (ring[u] && ring[v]) continue;
        dp[u][0] = min(dp[u][0], dp[v][1] + sum - dp[v][0]);
    }
}

int main() {
    scanf("%d", &n); f.init(n);
    for (int i = 1; i <= n; i++) scanf("%d", p + i);
    for (int i = 1; i <= n; i++) scanf("%d", d + i);
    vector<int> roots;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", fa + i); edge[fa[i]].push_back(i);
        if (!f.join(i, fa[i])) roots.push_back(i);
    }
    for (int rt: roots) {
        onring.clear(); getring(rt);
        for (int x: onring) ring[x] = 1;
        vector<ll> f, g, h;
        for (int x: onring) {
            dfs(x); 
            f.push_back(dp[x][0]);
            g.push_back(dp[x][1]);
            h.push_back(dp[x][1] - p[x]);
        }
        int sz = (int)onring.size();
        if (sz == 1) {
            ans += f[0]; continue;
        }
        ll res = inf;
        vector< pair<ll,ll> > dp(sz, {inf, inf});
        dp[0].first = f[0]; dp[0].second = g[0];
        for (int i = 1; i < sz; i++) {
            dp[i].second = g[i] + dp[i - 1].first;
            dp[i].first = min(dp[i - 1].second + h[i], f[i] + dp[i - 1].first);
        }
        res = dp[sz - 1].first;
        dp[0].first = h[0]; dp[0].second = inf;
        for (int i = 1; i < sz; i++) {
            dp[i].second = g[i] + dp[i - 1].first;
            dp[i].first = min(dp[i - 1].second + h[i], f[i] + dp[i - 1].first);
        }
        ans += min(res, dp[sz - 1].second);
    }
    cout << ans;
    return 0;
}