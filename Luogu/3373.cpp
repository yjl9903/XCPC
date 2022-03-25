#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, m, p;
ll a[maxn], sum[maxn << 2], add[maxn << 2], mul[maxn << 2];

void pushup(int rt){ sum[rt] = (sum[rt << 1] + sum[rt << 1 | 1]) % p; }
void pushdown(int rt, int ln, int rn){
    int ls = rt << 1, rs = rt << 1 | 1;
    if (mul[rt] != 1){
        mul[ls] *= mul[rt]; mul[rs] *= mul[rt];
        mul[ls] %= p; mul[rs] %= p;
        add[ls] *= mul[rt]; add[rs] *= mul[rt];
        add[ls] %= p; add[rs] %= p;
        sum[ls] *= mul[rt]; sum[rs] *= mul[rt];
        sum[ls] %= p; sum[rs] %= p;
        mul[rt] = 1;
    }
    if (add[rt] != 0){
        add[ls] += add[rt]; add[rs] += add[rt];
        add[ls] %= p; add[rs] %= p;
        sum[ls] += add[rt] * ln; sum[rs] += add[rt] * rn;
        sum[ls] %= p; sum[rs] %= p;
        add[rt] = 0;
    }
}
void build(int l, int r, int rt){
    mul[rt] = 1;
    if (l == r){
        sum[rt] = a[l] % p; return;
    }
    int m = l + r >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update1(int L, int R, int x, int l, int r, int rt){
    if (L <= l && r <= R){
        sum[rt] *= x; sum[rt] %= p; 
        mul[rt] *= x; mul[rt] %= p;
        add[rt] *= x; add[rt] %= p;
        return;
    }
    int m = l + r >> 1; pushdown(rt, m - l + 1, r - m);
    if (L <= m) update1(L, R, x, lson);
    if (R > m) update1(L, R, x, rson);
    pushup(rt);
}
void update2(int L, int R, int x, int l, int r, int rt){
    if (L <= l && r <= R){
        sum[rt] += x * (r - l + 1); sum[rt] %= p;
        add[rt] += x; add[rt] %= p;
        return;
    }
    int m = l + r >> 1; pushdown(rt, m - l + 1, r - m);
    if (L <= m) update2(L, R, x, lson);
    if (R > m) update2(L, R, x, rson);
    pushup(rt);
}
ll query(int L, int R, int l, int r, int rt){
    if (L <= l && r <= R) return sum[rt] % p;
    int m = l + r >> 1; ll ans = 0;
    pushdown(rt, m - l + 1, r - m);
    if (L <= m) ans += query(L, R, lson);
    ans %= p;
    if (R > m) ans += query(L, R, rson);
    return ans % p;
}

int main(){
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= n; i++) scanf("%lld", a + i);
    build(1, n, 1); int op, x, y, k;
    while (m--){
        scanf("%d", &op);
        if (op == 1){
            scanf("%d%d%d", &x, &y, &k);
            update1(x, y, k, 1, n, 1);
        }
        if (op == 2){
            scanf("%d%d%d", &x, &y, &k);
            update2(x, y, k, 1, n, 1);
        }
        if (op == 3){
            scanf("%d%d", &x, &y);
            printf("%lld\n", query(x, y, 1, n, 1));
        }
    }
    return 0;
}