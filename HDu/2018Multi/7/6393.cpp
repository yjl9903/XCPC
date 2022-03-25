#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

struct edge{int to, nxt, w;}f[maxn * 2];
int head[maxn], tot;
void add(int x, int y, int w){
    f[++tot] = {y, head[x], w}; head[x] = tot;
}
vector<edge> v;

int n, q, cutx, cuty, cutw, cuti;

int pre[maxn];
int find(int x){return x == pre[x] ? x : pre[x] = find(pre[x]);}
void join(int x, int y){
    x = find(x); y = find(y);
    pre[x] = y;
}

ll tree[maxn];
inline int lowbit(int x){return x & -x;}
void update(int i, ll x){
    while (i <= n){
        tree[i] += x;
        i += lowbit(i);
    }
}
ll query(int i){
    ll s = 0;
    while (i > 0){
        s += tree[i];
        i -= lowbit(i);
    }
    return s;
}

int dep[maxn], fa[maxn], siz[maxn], son[maxn], top[maxn], id[maxn], cnt;
void dfs(int x, int old, int d){
    dep[x] = d; fa[x] = old; siz[x] = 1; son[x] = 0;
    int m = -1;
    for (int i = head[x]; i; i = f[i].nxt){
        int v = f[i].to;
        if (v == old) continue;
        dfs(v, x, d + 1);
        siz[x] += siz[v];
        if (siz[v] > m) m = siz[v], son[x] = v;
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
void path(){
    for (int i = 0; i < v.size(); i++){
        if (v[i].w != -1){
            if (dep[v[i].to] < dep[v[i].nxt]) swap(v[i].nxt, v[i].to);
            update(id[v[i].to], v[i].w);
        }
    }
}

void upoint(int x, int y){
    int t = 0;
    if (dep[v[x].nxt] < dep[v[x].to]) t = id[v[x].to];
    else t = id[v[x].nxt];
    update(t, y - query(t) + query(t - 1));
}
ll qpath(int x, int y){
    ll ans = 0;
    while (top[x] != top[y]){
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        ans += query(id[x]) - query(id[top[x]] - 1);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    if (x != y) ans += query(id[y]) - query(id[x]);
    return ans;
}

void init(){
    v.clear(); ms(tree, 0); ms(head, 0); tot = cnt = 0;
    for (int i = 0; i <= n; i++) pre[i] = i;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &q); init();
        for (int i = 1, x, y, w; i <= n; i++){
            scanf("%d%d%d", &x, &y, &w);
            if (find(x) != find(y)){
                add(x, y, w); add(y, x, w);
                join(x, y);
                v.push_back({x, y, w});
            }
            else {
                cutx = x; cuty = y; cutw = w; cuti = i;
                v.push_back({-1, -1, -1});
            }
        }
        dfs(1, 0, 1); dfs(1, 1); path();
        int cmd, x, y;
        while (q--){
            scanf("%d%d%d", &cmd, &x, &y);
            if (cmd == 0){
                if (x == cuti) cutw = y;
                else upoint(x - 1, y);
            }
            else if (cmd == 1){
                ll ans = 1ll << 62;
                ans = min(ans, qpath(x, y));
                ans = min(ans, qpath(x, cutx) + qpath(cuty, y) + cutw);
                ans = min(ans, qpath(x, cuty) + qpath(cutx, y) + cutw);
                printf("%lld\n", ans);
            }
        }
    }
    return 0;
}