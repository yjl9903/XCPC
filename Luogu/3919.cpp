#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, m, a[maxn], root[maxn];

int ls[maxn * 40], rs[maxn * 40], b[maxn * 40], tot;
void update(int i, int x, int pre, int l, int r, int& rt) {
    rt = ++tot; ls[rt] = ls[pre]; rs[rt] = rs[pre];
    if (l == r) {
        b[rt] = x; return ;
    }
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, ls[pre], lson);
    else update(i, x, rs[pre], rson);
}
int query(int i, int l, int r, int rt) {
    if (rt == 0) return a[i];
    if (l == r) return b[rt];
    int m = (l + r) >> 1;
    if (i <= m) return query(i, lson);
    else return query(i, rson);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    int op, v, loc, x;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &v, &op, &loc);
        if (op == 1) {
            scanf("%d", &x);
            update(loc, x, root[v], 1, n, root[i]);
        } else if (op == 2) {
            printf("%d\n", query(loc, 1, n, root[v]));
            root[i] = root[v];
        }
    }
    return 0;
}