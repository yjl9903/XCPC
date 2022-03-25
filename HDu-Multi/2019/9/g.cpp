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
const int maxn = 100000 + 5;

int n, fa[maxn], dep[maxn], f[maxn], g[maxn], vis[maxn];
ll tag[maxn];
vector<int> edge[maxn];

void predfs(int u, int f) {
    dep[u] = dep[f] + 1; fa[u] = f;
    for (int v: edge[u]) {
        if (v == f) continue;
        predfs(v, u);
    }
}
void dfs(int u, int ff) {
    f[u] = g[u] = 1;
    for (int v: edge[u]) {
        if (v == ff || vis[v]) continue;
        dfs(v, u);
        g[u] = max(g[u], f[u] + f[v]);
        f[u] = max(f[u], f[v] + 1);
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            edge[i].clear(); vis[i] = tag[i] = 0;
        }
        for (int i = 2, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        predfs(1, 0);
        int rt = 1;
        for (int i = 2; i <= n; i++) if (dep[i] > dep[rt]) rt = i;
        predfs(rt, 0);
        rt = 1;
        for (int i = 2; i <= n; i++) if (dep[i] > dep[rt]) rt = i;
        vector<int> key;
        while (rt) {
            key.push_back(rt); 
            vis[rt] = 1;
            rt = fa[rt];
        }
        for (int x: key) dfs(x, 0);
        int sz = (int)key.size();
        vector<int> L(sz + 1, 0), R(sz + 1, 0);
        for (int i = 0; i < sz; i++) {
            int u = key[i];
            L[i] = i + f[u];
            R[i] = sz - 1 - i + f[u];
        }
        for (int i = 1; i < sz; i++) L[i] = max(L[i], L[i - 1]);
        for (int i = sz - 1; i >= 0; i--) R[i] = max(R[i], R[i + 1]);
        auto update = [&](int x, int y) {
            tag[x] = max(tag[x], 1ll * y);
            tag[y] = max(tag[y], 1ll * x);
        };
        for (int i = 0; i < sz; i++) update(L[i], R[i + 1]);
        for (int i = 1; i <= n; i++) if (!vis[i]) update(g[i], sz);
        ll ans = 0;
        for (int i = n; i >= 1; i--) {
            if (i < n) tag[i] = max(tag[i], tag[i + 1]);
            ans += tag[i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}