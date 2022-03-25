#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 300000 + 5;

int n, q, d[maxn], h[maxn], pre[maxn];

ll tr1[maxn << 2], tr2[maxn << 2];
void pushup(int rt) {
    tr1[rt] = max(tr1[rt << 1], tr1[rt << 1 | 1]);
    tr2[rt] = max(tr2[rt << 1], tr2[rt << 1 | 1]);
}
void build(int l, int r, int rt) {
    if (l == r) {
        tr1[rt] = h[l] * 2ll + pre[l];
        tr2[rt] = h[l] * 2ll - pre[l];
        return ;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
ll query1(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) return tr1[rt];
    int m = (l + r) >> 1; ll ans = 0;
    if (L <= m) ans = max(ans, query1(L, R, lson));
    if (R > m) ans = max(ans, query1(L, R, rson));
    return ans;
}
ll query2(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) return tr2[rt];
    int m = (l + r) >> 1; ll ans = 0;
    if (L <= m) ans = max(ans, query1(L, R, lson));
    if (R > m) ans = max(ans, query1(L, R, rson));
    return ans;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", d + i), pre[i] = pre[i - 1] + d[i];
    for (int i = 1; i <= n; i++) scanf("%d", h + i);
    for (int i = n + 1; i <= 2 * n; i++) pre[i] = pre[i - n], h[i] = h[i - n];
    build(1, 2 * n, 1);
    int a, b;
    while (q--) {
        scanf("%d%d", &a, &b);
        if (a <= b) {
            ll x = query1(b + 1, a + n - 1, 1, 2 * n, 1);
            ll y = query2(b + 1, a + n - 1, 1, 2 * n, 1);
            printf("%I64d\n", x + y);
        } else {
            ll x = query1(b + 1, a - 1, 1, 2 * n, 1);
            ll y = query2(b + 1, a - 1, 1, 2 * n, 1);
            printf("%I64d\n", x + y);
        }
    }
    return 0;
}