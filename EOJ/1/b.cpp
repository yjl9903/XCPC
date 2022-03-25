#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 1e9 + 7;
const int maxn = 1000000 + 5;

int n, q, eu[maxn], ev[maxn], dep[maxn];
vector<PII> edge[maxn];

namespace hld {
    int siz[maxn], fa[maxn], son[maxn], top[maxn];
    void dfs(int u, int f) {
        dep[u] = dep[f] + 1; fa[u] = f; siz[u] = 1; son[u] = 0;
        int m = -1;
        for (auto& x: edge[u]) {
            int v = x.first;
            if (v == f) continue;
            dfs(v, u);
            siz[u] += siz[v];
            if (siz[v] > m) son[u] = v, m = siz[v];
        }
    }
    void dfs(int u, int f, int tp) {
        top[u] = tp;
        if (!son[u]) return;
        dfs(son[u], u, tp); //
        for (auto& x: edge[u]) {
            int v = x.first;
            if (v == f || v == son[u]) continue;
            dfs(v, u, v);
        }
    }
    void init() {
        dfs(1, 0); dfs(1, 0, 1);
    }
    int qlca(int u, int v) {
        while (top[u] != top[v]){
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
}

int tag[maxn][2], ans[maxn], oud[maxn];
int dfs(int u, int f) {
    int a = tag[u][0], b = tag[u][1];
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f) continue;
        int r = dfs(v, u);
        dbg(u, v, r);
        if (r < 0) {
            if (eu[x.second] == u) ans[x.second] = -1;
            else ans[x.second] = 1;
            // assert(oud[v] == 0);
            oud[v]++;
            a = max(a, -r - 1);
        } else if (r > 0) {
            if (eu[x.second] == u) ans[x.second] = 1;
            else ans[x.second] = -1;
            // assert(oud[u] == 0);
            oud[u]++;
            b = max(b, r - 1);
        }
        assert(a == 0 || b == 0);
    }
    // assert(a == 0 || b == 0);
    if (a) return -a;
    if (b) return b;
    return 0;
}
void dfs2(int u, int f) {
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f) continue;
        dfs2(v, u);
        if (ans[x.second]) continue;
        if (oud[v] == 0) {
            if (eu[x.second] == u) ans[x.second] = -1;
            else ans[x.second] = 1;
            oud[v]++;
        } else if (oud[u] == 0) {
            if (eu[x.second] == u) ans[x.second] = 1;
            else ans[x.second] = -1;
            oud[u]++;
        } else {
            assert(0);
        }
    }
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; i++) edge[i].clear(), tag[i][0] = tag[i][1] = 0, ans[i] = 0, oud[i] = 0;
        for (int i = 2; i <= n; i++) {
            scanf("%d%d", eu + i, ev + i);
            edge[eu[i]].push_back({ev[i], i});
            edge[ev[i]].push_back({eu[i], i});
        }
        hld::init();
        int u, v;
        while (q--) {
            scanf("%d%d", &u, &v);
            int x = hld::qlca(u, v);
            // dbg(u, v, x);
            tag[u][0] = max(dep[u] - dep[x], tag[u][0]);
            tag[v][1] = max(dep[v] - dep[x], tag[v][1]);
        }
        // for (int i = 1; i <= n; i++) dbg(tag[i][0], tag[i][1]);
        dfs(1, 0); dfs2(1, 0);
        // for (int i = 1; i <= n; i++) assert(oud[i] <= 1);
        for (int i = 2; i <= n; i++) {
            if (ans[i] < 0) putchar('C');
            else putchar('D');
        }
        puts("");
    }
    return 0;
}