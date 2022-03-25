#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

void gmax(int& a, int b) {
    if (a < b) a = b;
}
struct node {
    int fi = -1, se = -1;
    void clear() {
        fi = se = -1;
    }
    void insert(int x) {
        if (x >= fi) se = fi, fi = x;
        else if (x > se) se = x;
    }
    int get(int x) {
        if (x == fi) return se;
        return fi;
    }
} a[maxn], b[maxn];

vector<PII> edge[maxn];
int n;

int f[maxn], g[maxn], up[maxn], h[maxn], ans, pos;
void join(int mn, int p) {
    if (mn < ans) ans = mn, pos = p;
    else if (mn == ans) pos = min(pos, p);
}

void dfs1(int u, int ff) {
    f[u] = 0; g[u] = inf;
    int sz = (int)edge[u].size();
    vector<int> pre(edge[u].size(), 0);
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == ff) continue;
        dfs1(v, u);
        f[u] = max(f[u], f[v] + x.second);
        // g[u] = max(g[u], min(f[v], g[v] + x.second));
    }
    g[u] = f[u];
    for (int i = 0; i < sz; i++) {
        int v = edge[u][i].first;
        if (v == ff) {
            pre[i] = i ? pre[i - 1] : 0; continue;
        }
        pre[i] = f[v] + edge[u][i].second;
        if (i) pre[i] = max(pre[i - 1], pre[i]);
    }
    int mx = 0;
    for (int i = sz - 1; i >= 0; i--) {
        int v = edge[u][i].first, w = edge[u][i].second;
        if (v == ff) continue;
        int tot = mx;
        if (i) gmax(tot, pre[i - 1]);
        gmax(tot, min(f[v], g[v] + w));
        g[u] = min(g[u], tot);
        mx = max(mx, f[v] + w);
    }
    // dbg(u, f[u], g[u]);
}
void dfs2(int u, int ff) {
    // dbg(u, g[u], up[u], f[u], h[u]);
    join(max(g[u], up[u]), u);
    join(max(f[u], h[u]), u);
    a[u].clear(); b[u].clear();
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == ff) continue;
        a[u].insert(f[v] + x.second);
    }
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == ff) continue;

        h[v] = max(h[u], a[u].get(f[v] + x.second)) + x.second;
        h[v] = min(h[v], max(up[u], a[u].get(f[v] + x.second)));

        up[v] = x.second + max(up[u], a[u].get(f[v] + x.second));
    }

    int sz = (int)edge[u].size();
    vector<int> suf(sz + 1, 0), suf2(sz + 1, 0); 
    suf[sz] = up[u]; suf2[sz] = up[u];
    for (int i = sz - 1; i >= 0; i--) {
        int v = edge[u][i].first, w = edge[u][i].second;
        if (v == ff) {
            suf[i] = suf[i + 1]; continue;
        }
        suf[i] = max(f[v] + w, suf[i + 1]);
        suf2[i] = min(max(suf2[i + 1], f[v] + w), max(suf[i + 1], min(f[v], g[v] + w)));
    }
    int mx = 0;
    for (int i = 0; i < sz; i++) {
        int v = edge[u][i].first, w = edge[u][i].second;
        if (v == ff) continue;
        int tot = max(mx, suf2[i + 1]) + w;
        h[v] = min(h[v], tot);
        mx = max(mx, f[v] + w);
    }

    reverse(edge[u].begin(), edge[u].end());
    for (int i = sz - 1; i >= 0; i--) {
        int v = edge[u][i].first, w = edge[u][i].second;
        if (v == ff) {
            suf[i] = suf[i + 1]; continue;
        }
        suf[i] = max(f[v] + w, suf[i + 1]);
        suf2[i] = min(max(suf2[i + 1], f[v] + w), max(suf[i + 1], min(f[v], g[v] + w)));
    }
    mx = 0;
    for (int i = 0; i < sz; i++) {
        int v = edge[u][i].first, w = edge[u][i].second;
        if (v == ff) continue;
        int tot = max(mx, suf2[i + 1]) + w;
        h[v] = min(h[v], tot);
        mx = max(mx, f[v] + w);
    }

    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == ff) continue;
        dfs2(v, u);
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) edge[i].clear();
        for (int i = 2, u, v, w; i <= n; i++) {
            scanf("%d%d%d", &u, &v, &w);
            edge[u].push_back({v, w});
            edge[v].push_back({u, w});
        }
        ans = inf; pos = -1;
        dfs1(1, 0);
        // a[1].insert(f[1]);
        up[1] = h[1] = 0;
        dfs2(1, 0);
        printf("%d %d\n", pos, ans);
    }
    return 0;
}