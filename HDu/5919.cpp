#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, m, cnt, a[maxn], root[maxn], tree[maxn * 40], ls[maxn * 40], rs[maxn * 40], vis[maxn];

void build(int l, int r, int& rt){
    rt = ++cnt; tree[rt] = 0;
    if (l == r) return;
    int m = (l + r) >> 1;
    build(lson); build(rson);
}
void update(int i, int x, int pre, int l, int r, int& rt){
    rt = ++cnt; ls[rt] = ls[pre]; rs[rt] = rs[pre]; tree[rt] = tree[pre] + x;
    if (l == r) return;
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, ls[pre], lson);
    else update(i, x, rs[pre], rson);
}
int query(int p, int l, int r, int rt){
    if (p == r) return tree[rt];
    int m = (l + r) >> 1;
    if (p <= m) return query(p, lson);
    else return query(p, rson) + tree[ls[rt]];
}
int kth(int k, int l, int r, int rt){
    if (l == r) return l;
    int m = (l + r) >> 1, s = tree[ls[rt]];
    if (k <= s) return kth(k, lson);
    else return kth(k - s, rson);
}

int main(){
    int T, kase = 0; scanf("%d", &T);
    while (T--){
        ms(vis, 0); cnt = 0;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        build(1, n, root[n + 1]);
        for (int i = n; i > 0; i--){
            if (vis[a[i]]){
                int tmp; update(vis[a[i]], -1, root[i + 1], 1, n, tmp);
                update(i, 1, tmp, 1, n, root[i]);
            }
            else {
                update(i, 1, root[i + 1], 1, n, root[i]);
            }
            vis[a[i]] = i;
        }
        
        printf("Case #%d:", ++kase);
        int last = 0, x, y, l, r;
        while (m--){
            scanf("%d%d", &x, &y);
            l = min((x + last) % n + 1, (y + last) % n + 1);
            r = max((x + last) % n + 1, (y + last) % n + 1);
            int s = query(r, 1, n, root[l]);
            int k = s / 2; if (s % 2) k++;
            last = kth(k, 1, n, root[l]);
            // printf("%d %d\n", l, r);
            // printf("%d\n", s);
            printf(" %d", last);
        }
        puts("");
    }
    return 0;
}