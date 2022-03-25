#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;

int n, k, q, a[maxn][32], tmp[5];

struct SegTree {
    int mx[maxn * 4], mn[maxn * 4];
    void pushup(int rt) { 
        mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
        mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
    }
    void build(int k, int l, int r, int rt) {
        if (l == r) {
            mx[rt] = mn[rt] = a[l][k]; return ;
        }
        int m = (l + r) >> 1;
        build(k, lson); build(k, rson);
        pushup(rt);
    }
    void update(int i, int x, int l, int r, int rt) {
        if (l == r) {
            mx[rt] = mn[rt] = x; return ;
        }
        int m = (l + r) >> 1;
        if (i <= m) update(i, x, lson);
        else update(i, x, rson);
        pushup(rt);
    }
    int qmin(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) return mn[rt];
        int m = (l + r) >> 1, ans = 1e9;
        if (L <= m) ans = min(ans, qmin(L, R, lson));
        if (R > m) ans = min(ans, qmin(L, R, rson));
        return ans;
    }
    int qmax(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) return mx[rt];
        int m = (l + r) >> 1, ans = -1e9;
        if (L <= m) ans = max(ans, qmax(L, R, lson));
        if (R > m) ans = max(ans, qmax(L, R, rson));
        return ans;
    }
} tr[32];


int main() {
    scanf("%d%d", &n, &k);
    int ss = 1 << k;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) scanf("%d", &tmp[j]);
        for (int s = 0; s < ss; s++) {
            int c = 0;
            for (int j = 0; j < k; j++) if (s & (1 << j)) c += tmp[j]; else c -= tmp[j];
            a[i][s] = c;
        }
    }
    for (int s = 0; s < ss; s++) tr[s].build(s, 1, n, 1);
    scanf("%d", &q);
    int op, l, r;
    while (q--) {
        scanf("%d%d", &op, &l);
        if (op == 1) {
            for (int i = 0; i < k; i++) scanf("%d", &tmp[i]);
            for (int s = 0; s < ss; s++) {
                int c = 0;
                for (int j = 0; j < k; j++) if (s & (1 << j)) c += tmp[j]; else c -= tmp[j];
                tr[s].update(l, c, 1, n, 1);
            }
        }
        if (op == 2) {
            scanf("%d", &r);
            int ans = 0;
            for (int s = 0; s < ss; s++) {
                ans = max(ans, tr[s].qmax(l, r, 1, n, 1) - tr[s].qmin(l, r, 1, n, 1));
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}