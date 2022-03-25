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

int n, m, q, key[maxn];
vector<PII> edge[maxn];

ll siz[maxn], cnt = 0; bool vis[maxn];
ll dfs(int u) {
    if (vis[u]) return siz[u];
    vis[u] = 1;
    siz[u] = key[u];
    for (auto& x: edge[u]) {
        int v = x.first;
        siz[u] += dfs(v);
    }
    return siz[u];
}
int tot, ans[sz + 5];
void dfs(int u, int d) {
    assert(tot < sz);
    if (u != 1 && key[u]) {
        ans[++tot] = d;
        if (tot == sz - 1) return ;
    }
    for (auto& x: edge[u]) {
        dfs(x.first, d + 1);
    }
}

int main() {
    int T, kase = 0; scanf("%d", &T);
    key[1] = 1;
    while (T--) {
        scanf("%d%d%d", &n, &m, &q);
        for (int i = 2; i <= n; i++) scanf("%d", key + i);
        for (int i = 1, u, v, w; i <= m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            edge[u].push_back({v, w});
        }
        for (int i = 1; i <= n; i++) {
            sort(edge[i].begin(), edge[i].end(), [](PII a, PII b) {
                if (a.second != b.second) return a.second < b.second;
                return a.first < b.first;
            });
        }
        tot = 0;
        cnt = dfs(1) - 1;
        // dbg(cnt);
        dfs(1, 0);
        // for (int i = 1; i <= cnt; i++) {
        //     dbg(i, ans[i]);
        // }
        printf("Case #%d:\n", ++kase);
        for (int i = 1, x; i <= q; i++) {
            scanf("%d", &x);
            if (x > cnt) puts("-1");
            else printf("%d\n", ans[x]);
        }
        for (int i = 1; i <= n; i++) siz[i] = vis[i] = 0, edge[i].clear();
        for (int i = 1; i <= min(1ll * (sz - 1), cnt); i++) ans[i] = 0;
    }
    return 0;
}