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
const int maxn = 300000 + 5;

inline int add(int x, int y) {
    x += y;
    return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
    x -= y;
    return x < 0 ? x += mod : x;
}
int f[maxn], inv[maxn], finv[maxn];
void init() {
    inv[1] = 1;
    for (int i = 2; i < maxn; i++) 
        inv[i] = (mod - mod / i) * 1ll * inv[mod % i] % mod;
    f[0] = finv[0] = 1; 
    for (int i = 1; i < maxn; i++) {
        f[i] = f[i - 1] * 1ll * i % mod;
        finv[i] = finv[i - 1] * 1ll * inv[i] % mod;
    }
}
int C(int n, int m) {
    if (m < 0 || m > n) return 0;
    return f[n] * 1ll * finv[n - m] % mod * finv[m] % mod;
}

vector<int> edge[maxn];

namespace hld {
    int dep[maxn], fa[maxn], siz[maxn], son[maxn], top[maxn];
    void dfs(int u, int f) {
        dep[u] = dep[f] + 1; fa[u] = f;
        siz[u] = 1; son[u] = 0;
        int m = -1;
        for (int v: edge[u]) {
            if (v == f) continue;
            dfs(v, u);
            siz[u] += siz[v];
            if (siz[v] > m) m = siz[v], son[u] = v;
        }
    }
    void dfs(int u, int f, int tp) {
        top[u] = tp;
        if (!son[u]) return ;
        dfs(son[u], u, tp);
        for (int v: edge[u]) {
            if (v == son[u] || v == f) continue;
            dfs(v, u, v);
        }
    }
    void build() {
        dfs(1, 0); dfs(1, 0, 1);
    }
    int qlca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
}
using hld::fa;
using hld::qlca;

int n, m, k, cnt[maxn], key[maxn];
PII path[maxn];

void dfs(int u, int f) {
    for (int v: edge[u]) {
        if (v == f) continue;
        dfs(v, u);
        cnt[u] += cnt[v];
    }
}

int main() {
    init();
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= n; i++) {
            edge[i].clear(); cnt[i] = key[i] = 0;
        }
        for (int i = 2, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        hld::build();
        for (int i = 1; i <= m; i++) {
            scanf("%d%d", &path[i].first, &path[i].second);
            int g = qlca(path[i].first, path[i].second);
            key[g]++;
            cnt[path[i].first]++;
            cnt[path[i].second]++;
            cnt[g]--;
            if (g > 1) cnt[fa[g]]--;
        }
        dfs(1, 0);
        for (int i = 1; i <= n; i++) {
            dbg(i, cnt[i], key[i]);
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = add(ans, C(cnt[i], k));
            ans = sub(ans, C(cnt[i] - key[i], k));
        }
        printf("%d\n", ans);
    }
    return 0;
}