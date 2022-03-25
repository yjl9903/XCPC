#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, q, a[maxn];

struct Seg {
    int sum[maxn << 2], add[maxn << 2], cov[maxn << 2];
    void pushup(int rt) { 
        sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    }
    void build(int l, int r, int rt) {
        cov[rt] = -1;
        if (l == r) return ;
        int m = (l + r) / 2;
        build(lson); build(rson);
    }
    void pushdown(int rt, int ln, int rn) {
        int ls = rt << 1, rs = rt << 1 | 1;
        if (cov[rt] != -1) {
            ll t = cov[rt];
            cov[ls] = cov[rs] = t;
            add[ls] = add[rs] = 0;
            sum[ls] = ln * t;
            sum[rs] = rn * t;
            // mul[ls] *= mul[rt]; mul[rs] *= mul[rt];
            // add[ls] *= mul[rt]; add[rs] *= mul[rt];
            // sum[ls] *= mul[rt]; sum[rs] *= mul[rt];
            cov[rt] = -1;
        }
        if (add[rt] != 0) {
            add[ls] ^= 1; add[rs] ^= 1;
            sum[ls] = ln - sum[ls];
            sum[rs] = rn - sum[rs];
            // add[ls] += add[rt]; add[rs] += add[rt];
            // sum[ls] += add[rt] * ln; sum[rs] += add[rt] * rn;
            add[rt] = 0;
        }
    }
    void updateXor(int L, int R, int x, int l = 1, int r = n, int rt = 1) {
        if (L <= l && r <= R) {
            sum[rt] = r - l + 1 - sum[rt];
            add[rt] ^= 1;
            // sum[rt] *= x;
            // mul[rt] *= x;
            // add[rt] *= x;
            return ;
        }
        int m = l + r >> 1; pushdown(rt, m - l + 1, r - m);
        if (L <= m) updateXor(L, R, x, lson);
        if (R > m) updateXor(L, R, x, rson);
        pushup(rt);
    }
    void updateCov(int L, int R, int x, int l = 1, int r = n, int rt = 1) {
        if (L <= l && r <= R) {
            sum[rt] = x * (r - l + 1);
            cov[rt] = x; add[rt] = 0;
            // sum[rt] += x * (r - l + 1);
            // add[rt] += x;
            return ;
        }
        int m = l + r >> 1; pushdown(rt, m - l + 1, r - m);
        if (L <= m) updateCov(L, R, x, lson);
        if (R > m) updateCov(L, R, x, rson);
        pushup(rt);
    }
    int query(int L, int R, int l = 1, int r = n, int rt = 1) {
        if (L <= l && r <= R) return sum[rt];
        int m = (l + r) / 2, ans = 0; pushdown(rt, m - l + 1, r - m);
        if (L <= m) ans = query(L, R, lson);
        if (R > m) ans += query(L, R, rson);
        return ans;
    }
} f[21];

int main() {
    scanf("%d", &n);
    for (int j = 0; j < 21; j++) f[j].build(1, n, 1);
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        for (int j = 0; j < 21; j++) {
            if (a[i] >> j & 1) {
                f[j].updateXor(i, i, 1);
            }
        }
    }
    scanf("%d", &q);
    int op, l, r, x;
    while (q--) {
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            ll sum = 0;
            for (int j = 0; j < 21; j++) {
                sum += (1ll << j) * f[j].query(l, r);
            }
            printf("%I64d\n", sum);
        } else if (op == 2) {
            scanf("%d", &x);
            for (int j = 0; j < 21; j++) {
                if (x >> j & 1) {
                    f[j].updateXor(l, r, 1);
                }
            }
        } else if (op == 3) {
            scanf("%d", &x);
            for (int j = 0; j < 21; j++) {
                if (x >> j & 1) {
                    f[j].updateCov(l, r, 1);
                }
            }
        } else {
            scanf("%d", &x);
            for (int j = 0; j < 21; j++) {
                if (x >> j & 1) ;
                else {
                    f[j].updateCov(l, r, 0);
                }
            }
        }
    }
    return 0;
}