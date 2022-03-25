#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

ll sum[maxn << 2], add[maxn << 2];
int n, q, a[maxn];

void pushup(int rt){ sum[rt] = sum[rt << 1] + sum[rt << 1 | 1]; }
void pushdown(int rt, int ln, int rn){
    if (add[rt]){
        add[rt << 1] += add[rt]; add[rt << 1 | 1] += add[rt];
        sum[rt << 1] += add[rt] * ln; sum[rt << 1 | 1] += add[rt] * rn;
        add[rt] = 0;
    }
}
void build(int l, int r, int rt){
    if (l == r){
        sum[rt] = 1ll * a[l];
        return;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, int x, int l, int r, int rt){
    if (L <= l && r <= R){
        sum[rt] += 1ll * x * (r - l + 1);
        add[rt] += 1ll * x;
        return;
    }
    int m = (l + r) >> 1;
    pushdown(rt, m - l + 1, r - m);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
}
ll query(int L, int R, int l, int r, int rt){
    if (L <= l && r <= R){
        return sum[rt];
    }
    int m = (l + r) >> 1;
    pushdown(rt, m - l + 1, r - m);
    ll ans = 0;
    if (L <= m) ans += query(L, R, lson);
    if (R > m) ans += query(L, R, rson);
    return ans;
}

int main(){
    while (~scanf("%d%d", &n, &q)){
        ms(sum, 0); ms(add, 0);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        build(1, n, 1);
        char cmd[5];
        while (q--){
            scanf("%s", cmd);
            if (cmd[0] == 'Q'){
                int l, r; scanf("%d%d", &l, &r);
                ll ans = query(l, r, 1, n, 1);
                printf("%lld\n", ans);
            }
            else if (cmd[0] == 'C'){
                int l, r, x; scanf("%d%d%d", &l, &r, &x);
                update(l, r, x, 1, n, 1);
            }
        }
    }
    return 0;
}