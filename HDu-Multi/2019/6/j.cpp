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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 2000 + 5;
const int maxv = 1000000 + 5;

inline int add(int x, int y) {
    x += y;
    return x >= mod ? x -= mod : x;
}

int n, m, w[maxn], vis[maxn], siz[maxn];
int val[maxv], ival[maxn];
vector<int> edge[maxn];

int sum, mn, mm, rt, ans;
void getrt(int u, int f) {
    siz[u] = 1;
    int mx = 0;
    for (int v: edge[u]) {
        if (v == f || vis[v]) continue;
        getrt(v, u);
        siz[u] += siz[v];
        mx = max(mx, siz[v]);
    }
    mx = max(mx, sum - siz[u]);
    if (mx < mn) mn = mx, rt = u;
}
int getrt(int u) {
    sum = siz[u]; mn = 1e9;
    getrt(u, 0); return rt;
}

int tot, dfn[maxn], rdfn[maxn], dp[maxn][maxn];
void dfs(int u, int f) {
    siz[u] = 1; dfn[u] = ++tot; rdfn[tot] = u;
    for (int v: edge[u]) {
        if (v == f || vis[v]) continue;
        dfs(v, u); siz[u] += siz[v];
    }
}
void solve(int u) {
    vis[u] = 1; tot = 0;
    dfs(u, 0);
    for (int i = 0; i <= mm; i++) dp[tot + 1][i] = 0;
    dp[tot + 1][1] = 1;
    for (int i = tot; i >= 1; i--) {
        int u = rdfn[i];
        for (int j = 1; j <= mm; j++) dp[i][j] = dp[i + siz[u]][j];
        for (int j = 1, k = 1; j <= mm; j++) {
            int v = val[j] / w[u];
            if (!v) continue;
            while (v < val[k]) k++;
            dp[i][k] = add(dp[i][k], dp[i + 1][j]);
            if (i == 1) ans = add(ans, dp[i + 1][j]);
        }
    }
    for (int v: edge[u]) {
        if (vis[v]) continue;
        solve(getrt(v));
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            edge[i].clear(); vis[i] = 0;
        }
        mm = 1; val[1] = m; ival[m] = 1;
        for (int i = 2; i <= m; i++) {
            if (m / i != m / (i - 1)) val[++mm] = m / i;
            // ival[m / i] = mm;
        }
        for (int i = 1; i <= n; i++) scanf("%d", w + i);
        for (int i = 2, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        siz[1] = n; ans = 0;
        solve(getrt(1));
        printf("%d\n", ans);
    }
    return 0;
}