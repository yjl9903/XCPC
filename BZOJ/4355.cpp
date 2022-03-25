#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int maxn = 300000 + 5;
const ll inf = 1ll << 61;

int n, m, a[maxn], sum[maxn << 2], cnt[maxn << 2];
ll add[maxn << 2], cov[maxn << 2], laz[maxn << 2], mn[maxn << 2], se[maxn << 2];

void pushup(int rt){
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    int ls = rt << 1, rs = rt << 1 | 1;
    if (mn[ls] == mn[rs]){
        mn[rt] = mn[ls]; cnt[rt] = cnt[ls] + cnt[rs];
        se[rt] = min(se[ls], se[rs]);
    }
    else if (mn[ls] < mn[rs]){
        mn[rt] = mn[ls]; cnt[rt] = cnt[ls];
        se[rt] = min(mn[rs], se[ls]);
    }
    else {
        mn[rt] = mn[rs]; cnt[rt] = cnt[rs];
        se[rt] = min(mn[ls], se[rs]);
    }
}
void pushdown(int rt, int ln, int rn){
    int ls = rt << 1, rs = rt << 1 | 1;
    if (cov[rt] != -1){
        ll& t = cov[rt]; 
        add[ls] = add[rs] = 0;
        laz[ls] = laz[rs] = -1;
        if (t == 0) sum[ls] = ln, sum[rs] = rn;
        else sum[ls] = sum[rs] = 0;
        mn[ls] = mn[rs] = t;
        cnt[ls] = ln; cnt[rs] = rn;
        se[ls] = se[rs] = inf;
        t = -1;
    }
    if (laz[rt] != -1){
        ll& t = laz[rt];

        t = -1;
    }
    if (add[rt] != 0){
        ll& t = add[rt];

        t = 0;
    }
}
void build(int l, int r, int rt){
    add[rt] = 0; cov[rt] = laz[rt] = -1;
    if (l == r){
        if (a[l] == 0) sum[rt] = 1; else sum[rt] = 0;
        mn[rt] = a[l]; cnt[rt] = 1; se[rt] = inf;
        return;
    }
    int m = l + r >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update1(int L, int R, int x, int l, int r, int rt){
    if (L <= l && r <= R){
        cov[rt] = x; add[rt] = 0; laz[rt] = -1;
        mn[rt] = x; cnt[rt] = r - l + 1; se[rt] = inf;
        if (x == 0) sum[rt] = r - l + 1;
        else sum[rt] = 0;
        return;
    }
    int m = l + r >> 1; 
    // pushdown(rt);
    if (l <= m) update1(L, R, x, lson);
    if (R > m) update1(L, R, x, rson);
    pushup(rt);
}
void update2(int L, int R, int x, int l, int r, int rt){
    if (L <= l && r <= R){
        add[rt] += x; mn[rt] += x; 
        if (se[rt] != inf) se[rt] += x;
        return;
    }
    int m = l + r >> 1; 
    // pushdown(rt);
    if (L <= m) update2(L, R, x, lson);
    if (R > m) update2(L, R, x, rson);
    pushup(rt);
}
void update(int L, int R, int l, int r, int rt){
    

    int m = l + r >> 1;
    if (L <= m) update(L, R, lson);
    if (R > m) update(L, R, rson);
    pushup(rt);
}

int query(int L, int R, int l, int r, int rt){
    if (L <= l && r <= R) return sum[rt];
    int m = l + r >> 1, ans = 0;

    if (L <= m) ans += query(L, R, lson);
    if (R > m) ans += query(L, R, rson);
    return ans;
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    build(1, n, 1); int op, l, r, c;
    while (m--){
        scanf("%d", &op);
        if (op == 1){
            scanf("%d%d%d", &l, &r, &c);
            update1(l, r, c, 1, n, 1);
        }
        if (op == 2){
            scanf("%d%d%d", &l, &r, &c);
            update2(l, r, c, 1, n, 1);

        }
        if (op == 3){
            scanf("%d%d%d", &l, &r);
            printf("%d\n", query(l, r, 1, n, 1));
        }
    }
    return 0;
}