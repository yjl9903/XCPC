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

int n, q, dfn[maxn], tot;
vector<int> edge[maxn];

namespace hld {
    int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
    void dfs(int u, int f) {
        dfn[u] = ++tot;
        dep[u] = dep[f] + 1; fa[u] = f; siz[u] = 1; son[u] = 0;
        int m = -1;
        for (auto& v: edge[u]) {
            if (v == f) continue;
            dfs(v, u);
            siz[u] += siz[v];
            if (siz[v] > m) son[u] = v, m = siz[v];
        }
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
}

int ans, key[maxn], sum[maxn];
namespace VT {
    int stk[maxn], top;
    void build(vector<int>& vec) {
        sort(vec.begin(), vec.end(), [](int a, int b) {
            return dfn[a] < dfn[b];
        });
        stk[top = 1] = 1; edge[1].clear();
        for (int x: vec) {
            if (x == 1) continue;
            int l = hld::qlca(stk[top], x);
            if (l != stk[top]) {
                while (dfn[stk[top - 1]] > dfn[l]) {
                    edge[stk[top - 1]].push_back(stk[top]); top--;
                }
                if (dfn[stk[top - 1]] < dfn[l]) {
                    edge[l].clear();
                    edge[l].push_back(stk[top]);
                    stk[top] = l;
                } else {
                    edge[l].push_back(stk[top]); top--;
                }
            }
            edge[x].clear(); stk[++top] = x;
        }
        for (int i = 1; i < top; i++) {
            edge[stk[i]].push_back(stk[i + 1]);
        }
    }
}
void dfs(int u) {
    sum[u] = key[u];
    if (key[u]) {
        for (int v: edge[u]) {
            dfs(v);
            if (sum[v]) ans++;
        }
    } else {
        for (int v: edge[u]) {
            dfs(v);
            if (sum[v]) sum[u]++;
        }
        if (sum[u] > 1) ans++, sum[u] = 0;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    hld::init();
    scanf("%d", &q); 
    while (q--) {
        int m; vector<int> vec; scanf("%d", &m);
        for (int i = 1, x; i <= m; i++) {
            scanf("%d", &x); vec.push_back(x); key[x] = 1;
        }
        int f = 0;
        for (int x: vec) if (key[hld::fa[x]]) f = 1;
        if (f) {
            for (int x: vec) key[x] = 0;
            puts("-1"); continue;
        }
        VT::build(vec);
        ans = 0; dfs(1);
        printf("%d\n", ans);
        for (int x: vec) key[x] = 0;
    }
    return 0;
}