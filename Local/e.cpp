#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

struct edge{int to, nxt;}f[maxn];
int head[maxn], tot = 0;
void add(int x, int y){
    f[++tot].to = y; f[tot].nxt = head[x]; head[x] = tot;
}

int cnt = 0, a[maxn], root[maxn], ls[maxn * 40], rs[maxn * 40], tree[maxn * 40];
void update(int i, int x, int pre, int l, int r, int &rt){
    rt = ++cnt; ls[rt] = ls[pre]; rs[rt] = rs[pre]; tree[rt] = tree[pre] + x;
    if (l == r) return;
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, ls[pre], lson);
    else update(i, x, rs[pre], rson);
}
int query(int v, int pre, int l, int r, int rt){
    if (l == r) return 1;
    int m = (l + r) >> 1;
    if (v <= m) return query(v, ls[pre], lson);
    else return query(v, rs[pre], rson) + tree[ls[rt]] - tree[ls[pre]];
}

int n, q, in[maxn], out[maxn];
void dfs(int p){
    in[p] = ++tot;
    update(a[p], 1, root[tot - 1], 1, n + 1, root[tot]);
    for (int i = head[p]; i; i = f[i].nxt){
        dfs(f[i].to);
    }
    out[p] = tot;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; i++) scanf("%d", a + i), a[i]++;
        tot = 0; ms(head, 0);
        for (int i = 2; i <= n; i++){
            int x, y; scanf("%d%d", &x, &y);
            add(x, y);
        }
        tot = cnt = 0; dfs(1);
        int r, v;
        while (q--){
            scanf("%d%d", &r, &v);
            printf("%d\n", query(a[v], root[in[r] - 1], 1, n + 1, root[out[r]]));
        }
    }
    return 0;
}