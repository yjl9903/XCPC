#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, k, p[maxn], q[maxn];
vector<int> edge[maxn];

namespace Tarjan {
    vector<int> st;
    int id, dfn[maxn], low[maxn], vis[maxn];
    int cnt, bel[maxn];
    void dfs(int u) {
        dfn[u] = low[u] = ++id;
        vis[u] = 1; st.push_back(u);
        for (int v: edge[u]) {
            if (!dfn[v]) {
                dfs(v); low[u] = min(low[u], low[v]);
            } else if (vis[v]) low[u] = min(low[u], dfn[v]);
        }
        if (dfn[u] == low[u]) {
            cnt--; int t = 0;
            do {
                t = st.back(); st.pop_back();
                bel[t] = cnt;
                vis[t] = 0;
            } while (t != u);
        }
    }
    void clear() { 
        ms(dfn, 0); ms(vis, 0);
        st.clear(); 
        id = 0; cnt = 26;
    }
}
using namespace Tarjan;

int main() {
    scanf("%d%d", &n, &k);
    clear();
    for (int i = 1; i <= n; i++) {
        scanf("%d", p + i);
        if (i > 1) {
            edge[p[i - 1]].push_back(p[i]);
        }
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", q + i);
        if (i > 1) {
            edge[q[i - 1]].push_back(q[i]);
        }
    }
    for (int i = 1; i <= n; i++) if (!dfn[p[i]]) dfs(p[i]);
    if (26 - cnt < k) return puts("No"), 0;
    puts("Yes");
    for (int i = 1; i <= n; i++) {
        printf("%c", max(0, bel[i]) + 'a');
    }
    return 0;
}