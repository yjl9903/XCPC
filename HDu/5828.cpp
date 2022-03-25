#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, q, a[maxn], mx[maxn << 2], mn[maxn << 2];
ll sum[maxn << 2], add[maxn << 2], cov[maxn << 2];

void pushup(int rt){
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
    mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
}
void pushdown(int rt, int ln, int rn){
    if (cov[rt] >= 0){
        sum[rt << 1] = cov[rt] * ln; sum[rt << 1 | 1] = cov[rt] * rn;
        cov[rt << 1] = cov[rt]; cov[rt << 1 | 1] = cov[rt];
        mx[rt << 1] = mn[rt << 1] = cov[rt];
        mx[rt << 1 | 1] = mn[rt << 1 | 1] = cov[rt];
        cov[rt] = -1; add[rt << 1] = add[rt << 1 | 1] = 0;
    }
    if (!add[rt]) return;
    sum[rt << 1] += add[rt] * ln; sum[rt << 1 | 1] += add[rt] * rn;
    add[rt << 1] += add[rt]; add[rt << 1 | 1] += add[rt];
    mx[rt << 1] += add[rt]; mx[rt << 1 | 1] += add[rt];
    mn[rt << 1] += add[rt]; mn[rt << 1 | 1] += add[rt];
    add[rt] = 0;
}
void build(int l, int r, int rt){
    add[rt] = 0; cov[rt] = -1;
    if (l == r){
        sum[rt] = mx[rt] = mn[rt] = a[l]; return;
    }
    int m = l + r >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, int x, int l, int r, int rt){
    if (L <= l && r <= R){
        sum[rt] += 1ll * (r - l + 1) * x; 
        mx[rt] += x; mn[rt] += x; add[rt] += x;
        return;
    }
    int m = l + r >> 1; pushdown(rt, m - l + 1, r - m);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
}
void update(int L, int R, int l, int r, int rt){
    if (L <= l && r <= R && mx[rt] - mn[rt] <= 1){
        int a = sqrt(mx[rt]), b = sqrt(mn[rt]);
        if (mx[rt] - mn[rt] == a - b){
            int x = a - mx[rt]; sum[rt] += 1ll * x * (r - l + 1);
            mx[rt] = a; mn[rt] = b; add[rt] += x;
        }
        else {
            sum[rt] = 1ll * a * (r - l + 1);
            mx[rt] = mn[rt] = a; 
            cov[rt] = a; add[rt] = 0;
        }
        return;
    }
    int m = l + r >> 1; pushdown(rt, m - l + 1, r - m);
    if (L <= m) update(L, R, lson);
    if (R > m) update(L, R, rson);
    pushup(rt);
}
ll query(int L, int R, int l, int r, int rt){
    if (L <= l && r <= R) return sum[rt];
    int m = l + r >> 1; ll ans = 0; 
    pushdown(rt, m - l + 1, r - m);
    if (L <= m) ans += query(L, R, lson);
    if (R > m) ans += query(L, R, rson);
    return ans;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        build(1, n, 1); int op, l, r, x;
        while (q--){
            scanf("%d", &op);
            if (op == 1){
                scanf("%d%d%d", &l, &r, &x);
                update(l, r, x, 1, n, 1);
            }
            if (op == 2){
                scanf("%d%d", &l, &r);
                update(l, r, 1, n, 1);
            }
            if (op == 3){
                scanf("%d%d", &l, &r);
                printf("%lld\n", query(l, r, 1, n, 1));
            }
        }
    }    
    return 0;
}