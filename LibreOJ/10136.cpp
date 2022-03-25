#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
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
const int mod = 998244353;
const int maxn = 500000 + 5;

vector<int> edge[maxn];
int n, q, dfn[maxn];

namespace hld {
    int siz[maxn], dep[maxn], son[maxn], fa[maxn], top[maxn], tot;
    void dfs(int u, int f) {
        siz[u] = 1; dep[u] = dep[f] + 1; fa[u] = f; dfn[u] = ++tot;
        int m = -1;
        for (int& v: edge[u]) {
            if (v == f) continue;
            dfs(v, u);
            siz[u] += siz[v];
            if (siz[v] > m) m = siz[v], son[u] = v;
        }
    }
    void dfs(int u, int f, int tp) {
        top[u] = tp;
        if (!son[u]) return;
        dfs(son[u], u, tp);
        for (int& v: edge[u]) {
            if (v == f || v == son[u]) continue;
            dfs(v, u, v);
        }
    }
    void init() {
        dfs(1, 0); dfs(1, 0, 1);
    }
    int qlca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
    int qdis(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[qlca(u, v)];
    }
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v); edge[v].push_back(u);
    } hld::init();
    int a[3], b[3];
    while (q--) {
        scanf("%d%d%d", a, a + 1, a + 2);
        for (int i = 0; i < 3; i++) b[i] = hld::qlca(a[i], a[(i + 1) % 3]);
        sort(a, a + 3, [](int a, int b) { return hld::dep[a] < hld::dep[b]; });
        sort(b, b + 3, [](int a, int b) { return hld::dep[a] < hld::dep[b]; });
        int ans = hld::qdis(a[0], a[1]) + hld::qdis(a[1], a[2]) + hld::qdis(a[2], a[0]);
        // dbg(a[0], a[1], a[2]);
        // dbg(hld::qlca(a[0], a[1]), hld::qlca(a[1], a[2]), hld::qlca(a[2], a[0]));
        // dbg(hld::qdis(a[0], a[1]), hld::qdis(a[1], a[2]), hld::qdis(a[2], a[0]));
        printf("%d %d\n", b[2], ans / 2);
    }
    return 0;
}