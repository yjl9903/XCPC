#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

vector<int> edge[maxn];

namespace hld {
    int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
    int tin[maxn], tout[maxn], tot;
    void dfs(int u, int f) {
        tin[u] = ++tot;
        dep[u] = dep[f] + 1; fa[u] = f; siz[u] = 1; son[u] = 0;
        int m = -1;
        for (auto& v: edge[u]) {
            if (v == f) continue;
            dfs(v, u);
            siz[u] += siz[v];
            if (siz[v] > m) son[u] = v, m = siz[v];
        }
        tout[u] = tot;
    }
    void dfs(int u, int f, int tp) {
        top[u] = tp;
        if (!son[u]) return;
        dfs(son[u], u, tp); // !
        for (auto& v: edge[u]) {
            if (v == f || v == son[u]) continue; // !
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
    int check(int x, int y) {
        return tin[x] <= tin[y] && tout[x] >= tout[y];
    }
}

int n, q;

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    hld::init();
    int kase = 0;
    while (q--) {
        int a, b, c, d; scanf("%d%d%d%d", &a, &b, &c, &d);
        int f = hld::qlca(a, b);
        int g = hld::qlca(c, d);
        int ans = 0;
        if (hld::check(f, g)) {
            if (hld::check(g, a) || hld::check(g, b)) ans = 1;
        }
        if (hld::check(g, f)) {
            if (hld::check(f, c) || hld::check(f, d)) ans = 1;
        }
        if (ans) puts("Y");
        else puts("N");
    }
    return 0;
}