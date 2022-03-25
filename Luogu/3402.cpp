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
const int maxn = 200000 + 5;

int n, m, root[maxn];

int tot, ls[maxn * 40], rs[maxn * 40], pre[maxn * 40], siz[maxn * 40];
void build(int l, int r, int& rt) {
    rt = ++tot;
    if (l == r) {
        pre[rt] = l; return ;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
}
void update(int i, int x, int last, int l, int r, int& rt) {
    rt = ++tot; ls[rt] = ls[last]; rs[rt] = rs[last];
    if (l == r) {
        pre[rt] = x; siz[rt] = siz[last]; return ;
    }
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, ls[last], lson);
    else update(i, x, rs[last], rson);
}
void add(int i, int l, int r, int& rt) {
    if (l == r) {
        siz[rt]++; return ;
    }
    int m = (l + r) >> 1;
    if (i <= m) add(i, lson);
    else add(i, rson);
}
int query(int i, int l, int r, int rt) {
    if (l == r) return rt;
    int m = (l + r) >> 1;
    if (i <= m) return query(i, lson);
    else return query(i, rson);
}

int find(int i, int x) {
    int p = query(x, 1, n, root[i]);
    return x == pre[p] ? p : find(i, pre[p]);
}
void join(int i, int x, int y) {
    x = find(i - 1, x); y = find(i - 1, y);
    if (pre[x] == pre[y]) return ;
    if (siz[x] > siz[y]) swap(x, y);
    update(pre[x], pre[y], root[i - 1], 1, n, root[i]);
    if (siz[x] == siz[y]) add(pre[y], 1, n, root[i]);
}

int main() {
    scanf("%d%d", &n, &m);
    build(1, n, root[0]);
    for (int i = 1, op, a, b; i <= m; i++) {
        scanf("%d%d", &op, &a);
        if (op == 1) {
            root[i] = root[i - 1];
            scanf("%d", &b);
            join(i, a, b);
        } else if (op == 2) {
            root[i] = root[a];
        } else if (op == 3) {
            scanf("%d", &b);
            root[i] = root[i - 1];
            a = find(i, a); b = find(i, b);
            if (pre[a] == pre[b]) puts("1");
            else puts("0");
        }
    }
    return 0;
}