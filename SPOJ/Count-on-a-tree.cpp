#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

struct edge{int to, nxt;}f[2 * maxn];
int head[maxn], tot = 0;
void add(int x, int y){f[++tot].to = y, f[tot].nxt = head[x], head[x] = tot;}

int n, q, len, a[maxn];
vector<int> v;

int ls[maxn * 40], rs[maxn * 40], tree[maxn * 40], root[maxn];
void update(int i, int pre, int l, int r, int &rt){
    rt = ++tot; ls[rt] = ls[pre]; rs[rt] = rs[pre]; tree[rt] = tree[pre] + 1;
    if (l == r) return;
    int m = (l + r) >> 1;
    if (i <= m) update(i, ls[pre], lson);
    else update(i, rs[pre], rson);
}
int query(int k, int L, int R, int r1, int r2, int l, int r){
    if (l == r) return l;
    int m = (l + r) >> 1;
    int s = tree[ls[L]] + tree[ls[R]] - tree[ls[r1]] - tree[ls[r2]];
    if (k <= s) return query(k, ls[L], ls[R], ls[r1], ls[r2], l, m);
    else return query(k - s, rs[L], rs[R], rs[r1], rs[r2], m + 1, r);
}

int dep[maxn], fa[maxn], siz[maxn], son[maxn], top[maxn], id[maxn], cnt = 0;
void dfs(int x, int g, int d){
    dep[x] = d; fa[x] = g; siz[x] = 1;
    update(a[x], root[g], 1, len, root[x]);
    int m = -1; 
    for (int i = head[x]; i; i = f[i].nxt){
        int v = f[i].to;
        if (v == g) continue;
        dfs(v, x, d + 1);
        siz[x] += siz[v];
        if (siz[v] > m) son[x] = v, m = siz[v];
    }
}
void dfs(int x, int tp){
    top[x] = tp; id[x] = ++cnt; 
    if (!son[x]) return;
    dfs(son[x], tp);
    for (int i = head[x]; i; i = f[i].nxt){
        int v = f[i].to;
        if (v == fa[x] || v == son[x]) continue;
        dfs(v, v);
    }
}

int lca(int x, int y){
    while (top[x] != top[y]){
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] > dep[y] ? y : x;
}
int qpath(int u, int v, int k){
    int l = lca(u, v);
    return query(k, root[u], root[v], root[l], root[fa[l]], 1, len);
}

int main(){
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), v.push_back(a[i]);
    sort(v.begin(), v.end()); vector<int>::iterator it = unique(v.begin(), v.end());
    v.resize(distance(v.begin(), it)); len = v.size();
    for (int i = 1; i <= n; i++) a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
    for (int i = 2, x, y; i <= n; i++){
        scanf("%d%d", &x, &y); add(x, y); add(y, x);
    }
    tot = 0;
    dfs(1, 0, 1); dfs(1, 1);
    int x, y, k;
    while (q--){
        scanf("%d%d%d", &x, &y, &k);
        printf("%d", v[qpath(x, y, k) - 1]);
        if (q) puts("");
    }
    return 0;
}