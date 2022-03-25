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
const int inf = 1e7 + 5;

bool check[inf]; int prime[inf];
void init(){
    int tot = 0; 
    for (int i = 2; i < inf; i++){
        if (!check[i]) prime[tot++] = i;
        for (int j = 0; j < tot && prime[j] * i < inf; j++){
            check[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
    for (int i = 0; i < inf; i++) check[i] ^= 1;
    for (int i = 2; i < inf; i *= 2) check[i] = 1;
    check[6] = 1;
}

int n, q, a[maxn], mx[maxn << 2], sum[maxn << 2];

void pushup(int rt){
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
}
void build(int l, int r, int rt){
    if (l == r) {
        mx[rt] = a[l]; 
        if (check[a[l]]) sum[rt] = 1; else sum[rt] = 0;
        return;
    }
    int m = l + r >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int i, int x, int l, int r, int rt){
    if (l == r){
        mx[rt] = x; 
        if (check[x]) sum[rt] = 1; else sum[rt] = 0;
        return;
    }
    int m = l + r >> 1;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    pushup(rt);
}
void update(int L, int R, int x, int l, int r, int rt){
    if (mx[rt] < x) return;
    if (L <= l && r <= R && l == r){
        mx[rt] = mx[rt] % x; 
        if (check[mx[rt]]) sum[rt] = 1; else sum[rt] = 0;
        return;
    }
    int m = l + r >> 1;
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
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
    init();
    while (~scanf("%d", &n)){
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        build(1, n, 1); scanf("%d", &q); int op, l, r, v;
        while (q--){
            scanf("%d", &op);
            if (op == 1){
                scanf("%d%d", &l, &r);
                printf("%d\n", query(l, r, 1, n, 1));
            }
            if (op == 2){
                scanf("%d%d%d", &l, &r, &v);
                update(l, r, v, 1, n, 1);
            }
            if (op == 3){
                scanf("%d%d", &l, &r);
                update(l, r, 1, n, 1);
            }
        }
    }
    return 0;
}