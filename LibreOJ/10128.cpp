#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, q, a[maxn];

ll sum[maxn << 2]; int mx[maxn << 2];
void pushup(int rt) {
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
}
void build(int l, int r, int rt) {
    if (l == r) {
        sum[rt] = mx[rt] = a[l]; return;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, int l, int r, int rt) {
    if (mx[rt] <= 1) return;
    if (l == r) {
        sum[rt] = mx[rt] = sqrt(mx[rt]); return;
    }
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, lson);
    if (R > m) update(L, R, rson);
    pushup(rt);
}
ll query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) return sum[rt];
    int m = (l + r) >> 1; ll ans = 0;
    if (L <= m) ans += query(L, R, lson);
    if (R > m) ans += query(L, R, rson);
    return ans;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    build(1, n, 1);
    scanf("%d", &q); int op, l, r;
    while (q--) {
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            printf("%lld\n", query(l, r, 1, n, 1));
        }
        if (op == 2) {
            update(l, r, 1, n, 1);
        }
    }
    return 0;
}