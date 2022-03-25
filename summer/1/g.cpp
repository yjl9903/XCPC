#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
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
const int maxn = 100000 + 10;
const int sz = 1e8 + 5;

struct Edge {
    int to, nxt;
} g[maxn];
int ecnt, head[maxn];
void add(int u, int v) {
    g[++ecnt] = { v, head[u] }; head[u] = ecnt;
}

int n, m, q, key[maxn];
vector<PII> edge[maxn];

ll siz[maxn], cnt = 0; bool vis[maxn];
ll dfs(int u) {
    if (vis[u]) return siz[u];
    vis[u] = 1;
    siz[u] = key[u];
    // for (auto& x: edge[u]) {
    //     int v = x.first;
    //     siz[u] += dfs(v);
    // }
    for (int i = head[u]; i; i = g[i].nxt) {
        siz[u] += dfs(g[i].to);
    }
    return siz[u];
}
int tot, ans[sz + 5];
void dfs(int u, int d) {
    if (tot == sz - 1) return ;
    assert(tot < sz);
    if (u != 1 && key[u]) {
        ans[++tot] = d;
        if (tot == sz - 1) return ;
    }
    // for (auto& x: edge[u]) {
    //     dfs(x.first, d + 1);
    // }
    for (int i = head[u]; i; i = g[i].nxt) {
        dfs(g[i].to, d + 1);
        if (tot == sz - 1) return ;
    }
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    key[1] = 1;
    while (T--) {
        ecnt = 0;
        scanf("%d%d%d", &n, &m, &q);
        for (int i = 2; i <= n; i++) scanf("%d", key + i);
        for (int i = 1, u, v, w; i <= m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            edge[u].push_back({v, w});
        }
        for (int i = 1; i <= n; i++) {
            sort(edge[i].begin(), edge[i].end(), [](PII a, PII b) {
                if (a.second != b.second) return a.second > b.second;
                return a.first > b.first;
            });
            for (auto& x: edge[i]) {
                add(i, x.first);
            }
        }
        tot = 0;
        cnt = dfs(1) - 1;
        dfs(1, 0);
        printf("Case #%d:\n", ++kase);
        for (int i = 1, x; i <= q; i++) {
            scanf("%d", &x);
            if (x > cnt) puts("-1");
            else printf("%d\n", ans[x]);
        }
        for (int i = 1; i <= n; i++) siz[i] = vis[i] = head[i] = 0, edge[i].clear();
        for (int i = 1; i <= min(1ll * (sz - 1), cnt); i++) ans[i] = 0;
    }
    return 0;
}