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
const int maxn = 100000 + 5;

// vector<PII> edge[maxn];
struct edge {
    int to, nxt, d;
} g[maxn * 2];
int head[maxn], tot;
void add(int u, int v, int w) {
    g[++tot] = {v, head[u], w}; head[u] = tot;
}

int n, k, dis[maxn], ans;

inline int lowbit(int x) { return x & -x; }
inline void update(int i, int x) {
    while (i < maxn) {
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
    if (d > k) return;
    vec.push_back(d);
    for (int i = head[u]; i; i = g[i].nxt) {
        int v = g[i].to;
        if (v == f || vis[v]) continue;
        dfs(v, u, d + g[i].d);
    }
}
void solve(int u) {
    vis[u] = 1;
    vector<int> al;
    for (int i = head[u]; i; i = g[i].nxt) {
        int v = g[i].to;
        if (vis[v]) continue;
        vec.clear();
        dfs(v, u, g[i].d);
        for (int& d: vec) {
            if (d == k) ans++;
            else ans += query(k - d) + 1;
        }
        for (int& d: vec) {
            update(d, 1); al.push_back(d);
        }
    }
    for (int& x: al) update(x, -1);
    for (int i = head[u]; i; i = g[i].nxt) {
        int v = g[i].to;
        if (vis[v]) continue;
        solve(getrt(v));
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2, u, v, w; i <= n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }
    scanf("%d", &k);
    siz[1] = n; 
    solve(getrt(1));
    cout << ans << endl;
    return 0;
}