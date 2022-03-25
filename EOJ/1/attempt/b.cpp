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
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 1e9 + 7;
const int maxn = 2000000 + 5;

vector<PII> edge[maxn];
int n, q, eu[maxn], ev[maxn];

namespace hld{
    int a[maxn * 4], b[maxn * 4], tag[maxn * 4];
    void build(int l, int r, int rt) {
        a[rt] = b[rt] = tag[rt] = 0;
        if (l == r) return;
        int m = l + r >> 1;
        build(lson); build(rson);
    }
    void pushdown(int rt) {
        if (!tag[rt]) return;
        if (tag[rt] == 1) {
            tag[rt << 1] = tag[rt << 1 | 1] = 1;
            a[rt << 1] = a[rt << 1 | 1] = 1;
        } else if (tag[rt] == -1) {
            tag[rt << 1] = tag[rt << 1 | 1] = -1;
            b[rt << 1] = b[rt << 1 | 1] = 1;
        }
        tag[rt] = 0;
    }
    int ans[maxn];
    void rebuild(int l, int r, int rt) {
        if (l == r) {
            if (a[rt]) ans[l] = 1;
            else ans[l] = -1;
            return;
        }
        int m = l + r >> 1;
        pushdown(rt);
        rebuild(lson); rebuild(rson);
    }
    void update(int L, int R, int x, int l, int r, int rt) {
        if (L <= l && r <= R) {
            if (x == 1) a[rt] = 1, tag[rt] = 1;
            else if (x == -1) b[rt] = 1, tag[rt] = -1;
            return;
        }
        int m = l + r >> 1; pushdown(rt);
        if (L <= m) update(L, R, x, lson);
        if (R > m) update(L, R, x, rson);
    }

    int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn], id[maxn], cnt;
    void dfs(int u, int f) {
        dep[u] = dep[f] + 1; siz[u] = 1; fa[u] = f;
        int m = - 1;
        son[u] = 0;
        for (auto& x: edge[u]) {
            int v = x.first;
            if (v == f) continue;
            dfs(v, u);
            siz[u] += siz[v];
            if (siz[v] > m) son[u] = v, m = siz[v];
        }
    }
    void dfs(int u, int f, int tp) {
        top[u] = tp; id[u] = ++cnt;
        if (!son[u]) return;
        dfs(son[u], u, tp);
        for (auto& x: edge[u]) {
            int v = x.first;
            if (v == f || v == son[u]) continue;
            dfs(v, u, v);
        }
    }

    void init() {
        build(1, n, 1);
        cnt = 0; dep[0] = 0;
        dfs(1, 0);
        dfs(1, 0, 1);
        // cout << "dep: ";for (int i = 1; i <= n; i++) cout << dep[i] << ' '; cout << endl;
        // cout << "fa:  ";for (int i = 1; i <= n; i++) cout << fa[i] << ' '; cout << endl;
        // cout << "top: ";for (int i = 1; i <= n; i++) cout << top[i] << ' '; cout << endl;
    }
    void upath(int u, int v) {
        // dbg(u, v);
        int du = -1, dv = 1;
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) {
                swap(u, v); swap(du, dv);
            }
            // dbg(u, v);
            // dbg(top[u], u, du);
            update(id[top[u]], id[u], du, 1, n, 1);
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) swap(u, v), swap(du, dv);
        // dbg(u, v, dv);
        if (id[u] < id[v]) update(id[u] + 1, id[v], dv, 1, n, 1);
    }
}

int ans[maxn];
void dfs(int u, int f) {
    for (auto& x: edge[u]) {
        int v = x.first, id = x.second;
        if (v == f) continue;
        // ans[x.second] = hld::ans[v];
        if (eu[id] == u) ans[id] = hld::ans[v];
        else ans[id] = -hld::ans[v];
        dfs(v, u);
    }
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &q);
        for (int i = 2, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            eu[i] = u; ev[i] = v;
            edge[u].push_back({v, i});
            edge[v].push_back({u, i});
        }
        hld::init();
        int u, v;
        while (q--) {
            scanf("%d%d", &u, &v);
            hld::upath(u, v); 
            // for (int i = 1; i <= n; i++) cout << hld::ans[i] << ' '; cout << endl;
        }
        hld::rebuild(1, n, 1);
        dfs(1, 0);
        for (int i = 2; i <= n; i++) {
            if (ans[i] > 0) putchar('D');
            else putchar('C');
        }
        puts("");
        for (int i = 0; i <= n; i++) edge[i].clear(), ans[i] = 0;
    }
    return 0;
}