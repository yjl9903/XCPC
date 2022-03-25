#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
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
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 1e9 + 7;
const int maxn = 200000 + 5;

struct node {
    int u, v, w;
    bool operator<(const node& b)const{
        return w > b.w;
    }
};

vector<int> lsh;
int gid(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
}

int n, m, pre[maxn];

vector<PII> edge[maxn];
int find(int x) { return x == pre[x] ? x : pre[x] = find(pre[x]); }

int tot, root[maxn], ls[maxn * 40], rs[maxn * 40], a[maxn * 40];
void update(int x, int pre, int l, int r, int& rt) {
    rt = ++tot; ls[rt] = ls[pre]; rs[rt] = rs[pre]; a[rt] = a[pre] + 1;
    if (l == r) return;
    int m = l + r >> 1;
    if (x <= m) update(x, ls[pre], lson);
    else update(x, rs[pre], rson);
}
int query(int pre, int l, int r, int rt) {
    if (l == r) return l;
    int m = l + r >> 1;
    // dbg(a[pre], a[rt]);
    if (a[rs[rt]] - a[rs[pre]]) return query(rs[pre], rson);
    else return query(ls[pre], lson);
}

int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
void dfs(int u, int f) {
    dep[u] = dep[f] + 1; siz[u] = 1; fa[u] = f;
    int m = -1;
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f) continue;
        update(gid(x.second), root[u], 1, lsh.size(), root[v]);
        dfs(v, u);
        siz[u] += siz[v];
        if (siz[v] > m) son[u] = v, m = siz[v];
    }
}
void dfs(int u, int f, int tp) {
    top[u] = tp;
    if (!son[u]) return;
    dfs(son[u], u, tp);
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f || v == son[u]) continue;
        dfs(v, u, v);
    }
}
int qlca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) pre[i] = i;
    priority_queue<node> pq; vector<node> v;
    for (int i = 1, u, v, w; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        pq.push({u, v, w}); lsh.push_back(w);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    while (!pq.empty()) {
        node t = pq.top(); pq.pop();
        int x = find(t.u), y = find(t.v);
        if (x == y) { 
            v.push_back(t);
            continue; 
        }
        pre[y] = x; 
        edge[t.u].push_back({t.v, t.w});
        edge[t.v].push_back({t.u, t.w});
    }
    dfs(1, 0); dfs(1, 0, 1);
    int ans = 0;
    for (auto& x: v) {
        int lca = qlca(x.u, x.v);
        if (x.u == lca) {
            if (query(root[lca], 1, lsh.size(), root[x.v]) == gid(x.w)) ans++;
            continue;
        } else if (x.v == lca) {
            if (query(root[lca], 1, lsh.size(), root[x.u]) == gid(x.w)) ans++;
            continue;
        }
        // dbg(x.u, x.v, x.w, lca);
        int a = query(root[lca], 1, lsh.size(), root[x.u]);
        int b = query(root[lca], 1, lsh.size(), root[x.v]);
        // dbg(a, b);
        if (max(a, b) == gid(x.w)) ans++;
    }
    cout << ans << endl;
    return 0;
}