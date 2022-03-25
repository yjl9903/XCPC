#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#ifdef XLor
  #define dbg(args...) do {cout << "debug -> "; err(args);} while (0)
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
const int maxn = 100000 + 5;

struct node{
    int u, v, c;
}; vector<node> v;

struct edge{int to, nxt;}g[2 * maxn];
int cnt, head[maxn];
void connect(int x, int y){
    g[++cnt].to = y; g[cnt].nxt = head[x]; head[x] = cnt; 
}

int n, m, k, wt[maxn << 2], add[maxn << 2], laz[maxn << 2], mx[maxn << 2], mn[maxn << 2];

int ans[maxn], nid[maxn];
void pushup(int rt){
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
    mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
}
void pushdown(int rt){
    // if (laz[rt] != -1) {
    //     wt[rt << 1] = wt[rt << 1 | 1] = laz[rt];
    //     laz[rt << 1] = laz[rt << 1 | 1] = laz[rt];
    //     laz[rt] = -1;
    // }
    if (add[rt]){
        mx[rt << 1] += add[rt]; mx[rt << 1 | 1] += add[rt];
        mn[rt << 1] += add[rt]; mn[rt << 1 | 1] += add[rt];
        add[rt << 1] += add[rt]; add[rt << 1 | 1] += add[rt];
        add[rt] = 0;
    }
}
void build(int l, int r, int rt){
    laz[rt] = -1;
    if (l == r) return;
    int m = l + r >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, int x, int l, int r, int rt){
    if (mn[rt] >= k) return;
    if (l == r && mx[rt] == k - 1){
        ans[nid[l]] = x;
        mx[rt]++; mn[rt]++;
        dbg(nid[l], mx[rt], x);
        return;
    }
    if (L <= l && r <= R && mx[rt] < k - 1){
        // wt[rt] = x; laz[rt] = x; 
        mx[rt]++; mn[rt]++; add[rt]++;
        // dbg(l, r, mn[rt], mx[rt]);
        return;
    }
    int m = l + r >> 1; pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
}
int query(int i, int l, int r, int rt){
    if (l == r) return wt[rt];
    int m = l + r >> 1; pushdown(rt);
    if (i <= m) return query(i, lson);
    else return query(i, rson);
}
int query2(int i, int l, int r, int rt){
    if (l == r) return mx[rt];
    int m = l + r >> 1; pushdown(rt);
    if (i <= m) return query2(i, lson);
    else return query2(i, rson);
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
    id[x] = ++cnt; nid[cnt] = x; wt[cnt] = 0; top[x] = tp;
    if (!son[x]) return;
    dfs2(son[x], tp);
    for (int i = head[x]; i; i = g[i].nxt){
        int v = g[i].to;
        if (v == son[x] || v == fa[x]) continue;
        dfs2(v, v);
    }
}
void upath(int x, int y, int k){
    while (top[x] != top[y]){
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        update(id[top[x]], id[x], k, 1, n, 1);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    update(id[x], id[y], k, 1, n, 1);
}

int main(){
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 2, x, y; i <= n; i++) {
        scanf("%d%d", &x, &y); connect(x, y); connect(y, x);
    }
    cnt = 0;
    dfs1(1, 0, 1); dfs2(1, 1); build(1, n, 1);
    for (int i = 1; i <= m; i++){
        int u, vv, c; scanf("%d%d%d", &u, &vv, &c);
        v.push_back(node{u, vv, c});
    }
    reverse(v.begin(), v.end());
    for (auto& x : v){
        dbg(x.u, x.v, x.c);
        upath(x.u, x.v, x.c); 
        // dbg('\n');
    }
    // for (int i = 1; i <= n; i++) printf("%d\n", query2(i, 1, n, 1));
    // for (int i = 1; i <= n; i++){
    //     if (i != 1) putchar(' ');
    //     if (query2(i, 1, n, 1) < k) putchar('0');
    //     else printf("%d", query(i, 1, n, 1));
    // }
    for (int i = 1; i <= n; i++){
        if (i != 1) putchar(' ');
        printf("%d", ans[i]);
    }
    return 0;
}