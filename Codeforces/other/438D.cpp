#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, m, a[maxn], mx[maxn << 2];;
ll sum[maxn << 2];

void pushup(int rt){
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
}
void build(int l, int r, int rt){
    if (l == r) {
        sum[rt] = mx[rt] = a[l]; return;
    }
    int m = l + r >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int i, int x, int l, int r, int rt){
    if (l == r){
        sum[rt] = mx[rt] = x; return;
    }
    int m = l + r >> 1;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    pushup(rt);
}
void update(int L, int R, int mod, int l, int r, int rt){
    if (L > r || l > R || mx[rt] < mod) return;
    if (L <= l && r <= R && l == r){
        sum[rt] = mx[rt] = mx[rt] % mod;
        return;
    }
    int m = l + r >> 1;
    update(L, R, mod, lson); update(L, R, mod, rson);
    pushup(rt);
}
ll query(int L, int R, int l, int r, int rt){
    if (L <= l && r <= R) return sum[rt];
    int m = l + r >> 1; ll ans = 0;
    if (L <= m) ans += query(L, R, lson); 
    if (R > m) ans += query(L, R, rson);
    return ans;
}

int main(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    build(1, n, 1); int op, l, r, k, x;
    while (m--){
        scanf("%d", &op);
        if (op == 1){
            scanf("%d%d", &l, &r); printf("%I64d\n", query(l, r, 1, n, 1));
        }
        if (op == 2){
            scanf("%d%d%d", &l, &r, &x); 
            update(l, r, x, 1, n, 1);
        }
        if (op == 3){
            scanf("%d%d", &k, &x);
            update(k, x, 1, n, 1);
        }
    }
    return 0;   
}