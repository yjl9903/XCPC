#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;

int n, q, a[maxn], b[maxn], pos[maxn];

int mx[maxn * 4], mn[maxn * 4], l1, r1;
void pushup(int rt) { 
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
    mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
}
void build(int l, int r, int rt) {
    if (l == r) {
        mx[rt] = mn[rt] = pos[b[l]]; return ;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int i, int x, int l, int r, int rt) {
    if (l == r) {
        mx[rt] = mn[rt] = pos[x]; return ;
    }
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    pushup(rt);
}
int query(int L, int R, int l, int r, int rt) {
    if (mn[rt] > r1 || mx[rt] < l1) return 0;
    if (L <= l && r <= R) {
        if (l1 <= mn[rt] && mx[rt] <= r1) return r - l + 1;
    }
    int m = (l + r) >> 1, ans = 0;
    if (L <= m) ans += query(L, R, lson);
    if (R > m) ans += query(L, R, rson);
    return ans;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), pos[a[i]] = i;
    for (int i = 1; i <= n; i++) scanf("%d", b + i);
    build(1, n, 1);
    int op, l2, r2, x, y;
    while (q--) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
            printf("%d\n", query(l2, r2, 1, n, 1));
        }
        if (op == 2) {
            scanf("%d%d", &x, &y);
            swap(b[x], b[y]);
            update(x, b[x], 1, n, 1);
            update(y, b[y], 1, n, 1);
        }
    }
    return 0;
}