#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;
const int maxk = 2e5 + 5;

// vector<PII> edge[maxn];
struct edge {
    int to, nxt, d;
} g[maxn * 2];
int head[maxn], tot;
void add(int u, int v, int w) {
    // g[++tot] = {v, head[u], w}; 
    g[++tot].to = v; g[tot].nxt = head[u]; g[tot].d = w;
    head[u] = tot;
}

int n, k, dis[maxk], ans;

inline int lowbit(int x) { return x & -x; }
inline void update(int i, int x) {
    while (i < maxk) {
        dis[i] += x; i += lowbit(i);
    }
}
inline int query(int i) {
    int r = 0; while (i > 0) r += dis[i], i -= lowbit(i);
    return r;
}

int siz[maxn], vis[maxn], rt, mn, sum;
void getrt(int u, int f) {
    siz[u] = 1; int t = 0;
    for (int i = head[u]; i; i = g[i].nxt) {
        int v = g[i].to;
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

vector<int> vec;
void dfs(int u, int f, int d) {
    vec.push_back(d);
    for (int i = head[u]; i; i = g[i].nxt) {
        int v = g[i].to;
        if (v == f || vis[v]) continue;
        dfs(v, u, d + g[i].d);
    }
}
int cal(int u, int tmp) {
    vec.clear();
    dfs(u, 0, tmp);
    sort(vec.begin(), vec.end());
    int ans = 0, l = 0, r = vec.size() - 1;
    while (l < r) {
        if (vec[l] + vec[r] <= k) ans += r - l, l++;
        else r--;
    }
    return ans;
}
void solve(int u) {
    vis[u] = 1;
    ans += cal(u, 0);
    for (int i = head[u]; i; i = g[i].nxt) {
        int v = g[i].to;
        if (vis[v]) continue;
        ans -= cal(v, g[i].d);
        solve(getrt(v));
    }
}

int main() {
    while (scanf("%d%d", &n, &k) == 2) {
        if (n == 0 && k == 0) return 0;
        if (k > (int)2e7) k = (int)2e7;
        ms(head, 0); ms(vis, 0); ms(dis, 0); tot = ans = 0;
        for (int i = 2, u, v, w; i <= n; i++) {
            scanf("%d%d%d", &u, &v, &w);
            add(u, v, w); add(v, u, w);
        }
        siz[1] = n; 
        solve(getrt(1));
        cout << ans << endl;
    }
    return 0;
}