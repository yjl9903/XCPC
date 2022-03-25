#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int gcd(int a, int b){return b == 0 ? a : gcd(b, a % b);}

struct edge{int to, nxt;}f[2 * maxn];
int head[maxn], tot = 0;
void add(int x, int y){
    f[++tot].to = y; f[tot].nxt = head[x]; head[x] = tot;
}

int n, m, a[maxn], wt[maxn], ans[maxn];

int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn], id[maxn], cnt = 0;
void dfs(int p, int d, int old){
    dep[p] = d; fa[p] = old; siz[p] = 1;
    int m = -1;
    for (int i = head[p]; i; i = f[i].nxt){
        int v = f[i].to;
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
    for (int i = head[p]; i; i = f[i].nxt){
        int v = f[i].to;
        if (v == fa[p] || v == son[p]) continue;
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

int main(){
    scanf("%d", &n); ms(ans, -1);
    for (int i = 2, x, y; i <= n; i++){
        scanf("%d", &x); add(x, i); 
    }
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    dfs(1, 1, 0); dfs(1, 1); 
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if (i == j) continue;
            int x = lca(i, j);
            ans[x] = max(ans[x], gcd(a[i], a[j]));
        }
    }
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}