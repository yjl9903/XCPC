#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
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
const int maxn = 100000 + 5;

inline int add(int x, int y) {
    x += y;
    return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
    x -= y;
    return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
    return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
    int r = 1;
    while (n > 0) {
        if (n & 1) r = 1ll * r * x % mod;
        n >>= 1; x = 1ll * x * x % mod;
    }
    return r;
}
inline int inv(int x) {
    return qpow(x, mod - 2);
}

int n;
vector<PII> edge[maxn];

int f[maxn][3], fc[maxn][3], g[maxn][3], gc[maxn][3], ans[3];
void dfs1(int u, int ff) {
    fc[u][0] = 1; fc[u][1] = fc[u][2] = 0;
    f[u][0] = f[u][1] = f[u][2] = 0;
    for (auto& x: edge[u]) {
        int v = x.first, w = x.second;
        if (v == ff) continue;
        dfs1(v, u);
        fc[u][w % 3] += fc[v][0];
        fc[u][(w + 1) % 3] += fc[v][1];
        fc[u][(w + 2) % 3] += fc[v][2];
        f[u][w % 3] = add(f[u][w % 3], add(f[v][0], mul(w, fc[v][0])));
        f[u][(w + 1) % 3] = add(f[u][(w + 1) % 3], add(f[v][1], mul(w, fc[v][1])));
        f[u][(w + 2) % 3] = add(f[u][(w + 2) % 3], add(f[v][2], mul(w, fc[v][2])));
    }
}

void dfs2(int u, int ff) {
    ans[0] = add(ans[0], g[u][0]);
    ans[1] = add(ans[1], g[u][1]);
    ans[2] = add(ans[2], g[u][2]);
    // dbg(u, ans[0], ans[1], ans[2]);

    for (auto& x: edge[u]) {
        int v = x.first, w = x.second;
        if (v == ff) continue;

        int tmp[3] = { g[u][0], g[u][1], g[u][2] };
        int tmpc[3] = { gc[u][0], gc[u][1], gc[u][2] };
        tmpc[w % 3] -= fc[v][0];
        tmpc[(w + 1) % 3] -= fc[v][1];
        tmpc[(w + 2) % 3] -= fc[v][2];
        tmp[w % 3] = sub(tmp[w % 3], add(f[v][0], mul(w, fc[v][0])));
        tmp[(w + 1) % 3] = sub(tmp[(w + 1) % 3], add(f[v][1], mul(w, fc[v][1])));
        tmp[(w + 2) % 3] = sub(tmp[(w + 2) % 3], add(f[v][2], mul(w, fc[v][2])));

        gc[v][w % 3] = fc[v][w % 3] + tmpc[0];
        gc[v][(w + 1) % 3] = fc[v][(w + 1) % 3] + tmpc[1];
        gc[v][(w + 2) % 3] = fc[v][(w + 2) % 3] + tmpc[2];
        g[v][0] = f[v][0];
        g[v][1] = f[v][1];
        g[v][2] = f[v][2];
        g[v][w % 3] = add(g[v][w % 3], add(tmp[0], mul(w, tmpc[0])));
        g[v][(w + 1) % 3] = add(g[v][(w + 1) % 3], add(tmp[1], mul(w, tmpc[1])));
        g[v][(w + 2) % 3] = add(g[v][(w + 2) % 3], add(tmp[2], mul(w, tmpc[2])));

        dfs2(v, u);
    }
}

int main() {
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; i++) edge[i].clear();
        for (int i = 2, u, v, w; i <= n; i++) {
            scanf("%d%d%d", &u, &v, &w); u++; v++;
            edge[u].push_back({v, w});
            edge[v].push_back({u, w});
        }
        ans[0] = ans[1] = ans[2] = 0;
        dfs1(1, 0);
        g[1][0] = f[1][0]; gc[1][0] = fc[1][0];
        g[1][1] = f[1][1]; gc[1][1] = fc[1][1];
        g[1][2] = f[1][2]; gc[1][2] = fc[1][2];
        // cout << f[1][0] << ' ' << f[1][1] << ' ' << f[1][2];
        dfs2(1, 0);
        printf("%d %d %d\n", ans[0], ans[1], ans[2]);
    }
    return 0;
}