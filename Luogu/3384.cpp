#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

struct edge{int to, nxt;}g[2 * maxn];
int cnt, head[maxn];
void connect(int x, int y){
    g[++cnt].to = y; g[cnt].nxt = head[x]; head[x] = cnt; 
}

int n, m, r, p, a[maxn], wt[maxn], tree[maxn << 2], add[maxn << 2];

void pushup(int rt){ tree[rt] = (tree[rt << 1] + tree[rt << 1 | 1]) % p; }
void pushdown(int rt, int ln, int rn){
    if (!add[rt]) return;
    tree[rt << 1] = (tree[rt << 1] + add[rt] * ln % p) % p;
    tree[rt << 1 | 1] = (tree[rt << 1 | 1] + add[rt] * rn % p) % p;
    add[rt << 1] = (add[rt << 1] + add[rt]) % p;
    add[rt << 1 | 1] = (add[rt << 1 | 1] + add[rt]) % p;
    add[rt] = 0;
}
void build(int l, int r, int rt){
    if (l == r){
        add[rt] = 0;
        tree[rt] = wt[l] % p;
        return;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, int x, int l, int r, int rt){
    if (L <= l && r <= R){
        tree[rt] += x * (r - l + 1); tree[rt] %= p;
        add[rt] += x; add[rt] %= p;
        return;
    }
    int m = (l + r) >> 1;
    pushdown(rt, m - l + 1, r - m);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
}
int query(int L, int R, int l, int r, int rt){
    if (L <= l && r <= R) return tree[rt];
    int m = (l + r) >> 1, s = 0;
    pushdown(rt, m - l + 1, r - m);
    if (L <= m) s += query(L, R, lson);
    s %= p;
    if (R > m) s += query(L, R, rson);
    return s % p;
}

int dep[maxn], fa[maxn], siz[maxn], son[maxn], id[maxn], top[maxn];
void dfs1(int x, int f, int deep){
    dep[x] = deep; fa[x] = f; siz[x] = 1;
    int maxs = -1;
    for (int i = head[x]; i; i = g[i].nxt){
        int v = g[i].to;
        if (v == fa[x]) continue;
        dfs1(v, x, deep + 1);
        siz[x] += siz[v];
        if (siz[v] > maxs) son[x] = v, maxs = siz[v];
    }
}
void dfs2(int x, int tp){
    id[x] = ++cnt; wt[cnt] = a[x]; top[x] = tp;
    if (!son[x]) return;
    dfs2(son[x], tp);
    for (int i = head[x]; i; i = g[i].nxt){
        int v = g[i].to;
        if (v == son[x] || v == fa[x]) continue;
        dfs2(v, v);
    }
}

int qpath(int x, int y){
    int ans = 0;
    while (top[x] != top[y]){
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        ans = (ans + query(id[top[x]], id[x], 1, n, 1)) % p;
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    ans = (ans + query(id[x], id[y], 1, n, 1)) % p;
    return ans;
}
int qson(int x){
    return query(id[x], id[x] + siz[x] - 1, 1, n, 1);
}
void upath(int x, int y, int k){
    k %= p;
    while (top[x] != top[y]){
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        update(id[top[x]], id[x], k, 1, n, 1);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    update(id[x], id[y], k, 1, n, 1);
}
void uson(int x, int k){
    update(id[x], id[x] + siz[x] - 1, k % p, 1, n, 1);
}

int main(){
    scanf("%d%d%d%d", &n, &m, &r, &p);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    cnt = 0;
    for (int i = 2; i <= n; i++){
        int x, y; scanf("%d%d", &x, &y);
        connect(x, y); connect(y, x);
    }
    cnt = 0;
    dfs1(r, 0, 1); dfs2(r, r);
    build(1, n, 1);
    int cmd, x, y, z;
    while (m--){
        scanf("%d", &cmd);
        if (cmd == 1){
            scanf("%d%d%d", &x, &y, &z);
            upath(x, y, z);
        }
        if (cmd == 2){
            scanf("%d%d", &x, &y);
            printf("%d\n", qpath(x, y));
        }
        if (cmd == 3){
            scanf("%d%d", &x, &y);
            uson(x, y);
        }
        if (cmd == 4){
            scanf("%d", &x);
            printf("%d\n", qson(x));
        }
    }
    return 0;
}