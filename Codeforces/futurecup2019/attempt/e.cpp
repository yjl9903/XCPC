#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <assert.h>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;
const int maxv = 100000;

int n, q, a[maxn];

int c[maxn << 2], b[maxn << 2], cov[maxn << 2], rev[maxn << 2];
void pushdown(int rt) {
    int ls = rt << 1, rs = rt << 1 | 1;
    assert(cov[rt] == 0 || rev[rt] == 0);
    if (cov[rt]) {
        int t = cov[rt];
        cov[ls] = cov[rs] = b[ls] = b[rs] = t;
        rev[rs] = rev[ls] = c[ls] = c[rs] = 0;
        cov[rt] = 0;
    }
    if (rev[rt]) {
        int t = rev[rt];
        if (b[ls]) {
            b[ls] = -b[ls]; cov[ls] = b[ls];
            rev[ls] = c[ls] = 0;
        } else {
            c[ls] ^= 1; rev[ls] ^= 1;
        }
        if (b[rs]) {
            b[rs] = -b[rs]; cov[rs] = b[rs];
            rev[rs] = c[rs] = 0;
        } else {
            c[rs] ^= 1; rev[rs] ^= 1;
        }
        rev[rt] = 0;
    }
}
void update1(int L, int R, int x, int l, int r, int rt) {
    if (L <= l && r <= R) {
        b[rt] = x; cov[rt] = x; rev[rt] = c[rt] = 0;
        return ;
    }
    // dbg(l, r, rt);
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update1(L, R, x, lson);
    if (R > m) update1(L, R, x, rson);
}
void update2(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) {
        if (b[rt]) {
            b[rt] = -b[rt]; cov[rt] = b[rt];
            rev[rt] = c[rt] = 0;
        } else {
            c[rt] ^= 1; rev[rt] ^= 1;
        } 
        return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update2(L, R, lson);
    if (R > m) update2(L, R, rson);
}
int d[maxn];
void build(int l, int r, int rt) {
    if (l == r) {
        if (b[rt]) {
            if (c[rt]) {
                d[l] = -b[rt];
            } else {
                d[l] = b[rt];
            }
        } else {
            if (c[rt]) d[l] = 2;
            else d[l] = 0;
        }
        return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    build(lson); build(rson);
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    char op[2]; int x;
    while (q--) {
        scanf("%s%d", op, &x);
        if (op[0] == '<') {
            if (x <= 0) {
                update1(-x + 1, maxv, 1, 1, maxv, 1);
            } else {
                update1(x, maxv, 1, 1, maxv, 1);
                if (x == 1) continue;
                update2(1, x - 1, 1, maxv, 1);
            }
        } else if (op[0] == '>') {
            if (x >= 0) {
                update1(x + 1, maxv, -1, 1, maxv, 1);
            } else {
                update1(-x, maxv, -1, 1, maxv, 1);
                if (x == -1) continue;
                update2(1, -x - 1, 1, maxv, 1);
            }
        }
        build(1, maxv, 1);
        for (int i = 1; i <= 5; i++) {
            dbg(d[i]);
        }
        // for (int i = 1; i <= n; i++) {
        //     int t = d[abs(a[i])];
        //     if (t == 0) printf("%2d ", a[i]);
        //     else if (t == 1) printf("%2d ", abs(a[i]));
        //     else if (t == -1) printf("%2d ", -abs(a[i]));
        //     else printf("%2d ", -a[i]);
        // }
        puts("");
    }
    build(1, maxv, 1);
    for (int i = 1; i <= n; i++) {
        int t = d[abs(a[i])];
        if (t == 0) printf("%d ", a[i]);
        else if (t == 1) printf("%d ", abs(a[i]));
        else if (t == -1) printf("%d ", -abs(a[i]));
        else printf("%d ", -a[i]);
    }
    return 0;
}