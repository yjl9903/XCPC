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
const int maxn = 1000 + 5;

vector<int> edge[maxn];
int n, x[maxn], y[maxn], c[maxn], r[maxn];

namespace Tarjan {
    vector<int> st;
    int id, dfn[maxn], low[maxn], vis[maxn];
    int cnt, bel[maxn], ind[maxn], oud[maxn], mn[maxn];
    void dfs(int u) {
        dfn[u] = low[u] = ++id;
        vis[u] = 1; st.push_back(u);
        for (int i = 0; i < edge[u].size(); i++) {
            int v = edge[u][i];
            if (!dfn[v]) {
                dfs(v); low[u] = min(low[u], low[v]);
            } else if (vis[v]) low[u] = min(low[u], dfn[v]);
        }
        if (dfn[u] == low[u]) {
            cnt++; int t = 0;
            do {
                t = st.back(); st.pop_back();
                bel[t] = cnt;
                vis[t] = 0;
            } while (t != u);
        }
    }
    void clear() { 
        ms(dfn, 0); ms(vis, 0);
        ms(ind, 0); ms(oud, 0);
        st.clear(); 
        cnt = id = 0; 
    }
}
using namespace Tarjan;

int main() {
    int T, kase = 0; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d%d", x + i, y + i, r + i, c + i);
            edge[i].clear();
        }
        auto dis = [&](int i, int j) -> ll {
            return 1ll * (x[i] - x[j]) * (x[i] - x[j]) + 1ll * (y[i] - y[j]) * (y[i] - y[j]);
        };
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j) continue;
                if (dis(i, j) <= 1ll * r[i] * r[i]) {
                    edge[i].push_back(j);
                }
            }
        }
        clear();
        for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(i);
        for (int i = 1; i <= cnt; i++) mn[i] = inf;
        for (int i = 1; i <= n; i++) {
            // dbg(i, bel[i]);
            mn[bel[i]] = min(mn[bel[i]], c[i]);
            for (int v: edge[i]) {
                int x = bel[i], y = bel[v];
                if (x == y) continue;
                oud[x]++; ind[y]++;
            }
        }
        int ans = 0;
        for (int i = 1; i <= cnt; i++) if (ind[i] == 0) ans += mn[i];
        printf("Case #%d: %d\n", ++kase, ans);
    }
    return 0;
}