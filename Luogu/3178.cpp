#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

// struct edge{int to, nxt;}f[2 * maxn];
// int head[maxn], tot = 0;
// void add(int x, int y){
//     f[++tot].to = y; f[tot].nxt = head[x]; head[x] = tot;
// }
int to[maxn << 1], nxt[maxn << 1], head[maxn], tot = 0;
void add(int x, int y){
    to[++tot] = y; nxt[tot] = head[x]; head[x] = tot;
}

int n, m, a[maxn];

namespace hld{
    ll wt[maxn], tree[maxn << 2], laz[maxn << 2];
    void pushup(int rt){tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];}
    void pushdown(int rt, int ln, int rn){
        if (!laz[rt]) return;
        tree[rt << 1] += 1ll * laz[rt] * ln; tree[rt << 1 | 1] += 1ll * laz[rt] * rn;
        laz[rt << 1] += 1ll * laz[rt]; laz[rt << 1 | 1] += 1ll * laz[rt];
        laz[rt] = 0;
    }
    void build(int l, int r, int rt){
        if (l == r){
            laz[rt] = 0; tree[rt] = wt[l];
            return;
        }
        int m = (l + r) >> 1;
        build(lson); build(rson);
        pushup(rt);
    }
    void update(int i, int x, int l, int r, int rt){
        if (l == r){
            tree[rt] += 1ll * x;
            return;
        }
        int m = (l + r) >> 1; pushdown(rt, m - l + 1, r - m);
        if (i <= m) update(i, x, lson);
        else update(i, x, rson);
        pushup(rt);
    }
    void update(int L, int R, int x, int l, int r, int rt){
        if (L <= l && r <= R){
            tree[rt] += 1ll * x * (r - l + 1); laz[rt] += 1ll * x;
            return;
        }
        int m = (l + r) >> 1; pushdown(rt, m - l + 1, r - m);
        if (L <= m) update(L, R, x, lson);
        if (R > m) update(L, R, x, rson);
        pushup(rt);
    }
    ll query(int L, int R, int l, int r, int rt){
        if (L <= l && r <= R) return tree[rt];
        int m = (l + r) >> 1; pushdown(rt, m - l + 1, r - m);
        ll s = 0;
        if (L <= m) s += query(L, R, lson);
        if (R > m) s += query(L, R, rson);
        return s;
    }

    int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn], id[maxn], cnt = 0;
    void dfs(int p, int d, int old){
        dep[p] = d; fa[p] = old; siz[p] = 1;
        int m = -1;
        for (int i = head[p]; i; i = nxt[i]){
            int v = to[i];
            if (v == fa[p]) continue;
            dfs(v, d + 1, p);
            siz[p] += siz[v];
            if (siz[v] > m) son[p] = v, m = siz[v];
        }
    }
    void dfs(int p, int tp){
        id[p] = ++cnt; top[p] = tp; wt[cnt] = a[p];
        if (!son[p]) return;
        dfs(son[p], tp);
        for (int i = head[p]; i; i = nxt[i]){
            int v = to[i];
            if (v == fa[p] || v == son[p]) continue;
            dfs(v, v);
        }
    }
    void init(){
        cnt = 0; dfs(1, 1, 0); dfs(1, 1); build(1, n, 1);
    }
}
using namespace hld;

ll qpath(int x){
    ll ans = 0;
    while (top[x] != top[1]){
        ans += query(id[top[x]], id[x], 1, n, 1);
        x = fa[top[x]];
    }
    ans += query(id[1], id[x], 1, n, 1);
    return ans;
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 2, x, y; i <= n; i++){
        scanf("%d%d", &x, &y); add(x, y); add(y, x);
    }
    // dfs(1, 1, 0); dfs(1, 1); build(1, n, 1);
    init();
    int cmd, x, a;
    while (m--){
        scanf("%d", &cmd);
        if (cmd == 1){
            scanf("%d%d", &x, &a);
            update(id[x], id[x], a, 1, n, 1);
        }
        else if (cmd == 2){
            scanf("%d%d", &x, &a);
            update(id[x], id[x] + siz[x] - 1, a, 1, n, 1);
        }
        else if (cmd == 3){
            scanf("%d", &x); printf("%lld\n", qpath(x));
        }
    }
    return 0;
}