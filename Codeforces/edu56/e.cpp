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
const int maxn = 200000 + 5;

vector<int> nodes; int nid;
int tot, root[maxn], ls[maxn * 150], rs[maxn * 150], cnt[maxn * 150];
int node() {
    if (nodes.empty()) return ++nid;
    int r = nodes.back(); nodes.pop_back();
    return r;
}
void del(int& x) {
    ls[x] = rs[x] = cnt[x] = 0;
    nodes.push_back(x); x = 0;
}

int n, q, a[maxn], b[maxn], pos[maxn];

int l1, r1, l2, r2;
void update(int i, int x, int l, int r, int& rt) {
    if (!rt) rt = node(); cnt[rt] += x;
    if (l == r) {
        if (!cnt[rt]) del(rt), rt = 0;
        return ;
    }
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    if (!cnt[rt]) del(rt), rt = 0;
}
int query(int L, int R, int l, int r, int rt) {
    if (!rt) return 0;
    if (L <= l && r <= R) return cnt[rt];
    int m = (l + r) >> 1, ans = 0;
    if (L <= m) ans += query(L, R, lson);
    if (R > m) ans += query(L, R, rson);
    return ans;
}
inline int lowbit(int x) { return x & -x; }
inline void update(int i, int x) {
    int p = pos[b[i]];
    for (; i <= n; i += lowbit(i)) update(p, x, 1, n, root[i]);
}
inline int query() {
    int ans = 0;
    for (int i = l2 - 1; i > 0; i -= lowbit(i)) ans -= query(l1, r1, 1, n, root[i]);
    for (int i = r2; i > 0; i -= lowbit(i)) ans += query(l1, r1, 1, n, root[i]);
    return ans;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), pos[a[i]] = i;
    for (int i = 1; i <= n; i++) scanf("%d", b + i);
    for (int i = 1; i <= n; i++) update(i, 1);
    int op, x, y;
    while (q--) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
            printf("%d\n", query());
        }
        if (op == 2) {
            scanf("%d%d", &x, &y);
            update(x, -1); update(y, -1);
            swap(b[x], b[y]);
            update(x, 1); update(y, 1);
        }
    }
    return 0;
}