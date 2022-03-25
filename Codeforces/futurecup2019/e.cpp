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

struct Tree { 
    int b[maxn << 2], cov[maxn << 2], rev[maxn << 2];
    void pushdown(int rt) {
        int ls = rt << 1, rs = rt << 1 | 1;
        if (cov[rt]) {
            int t = cov[rt];
            cov[ls] = cov[rs] = b[ls] = b[rs] = t;
            cov[rt] = rev[rt] = 0;
        } else if (rev[rt]) {
            b[ls] = -b[ls]; b[rs] = -b[rs];
            if (cov[ls]) cov[ls] = -cov[ls]; else rev[ls] ^= 1;
            if (cov[rs]) cov[rs] = -cov[rs]; else rev[rs] ^= 1;
            rev[rt] = 0;
        }
    }
    void update1(int L, int R, int x, int l, int r, int rt) {
        if (L <= l && r <= R) {
            b[rt] = x; cov[rt] = x; return ;
        }
        int m = (l + r) / 2; pushdown(rt);
        if (L <= m) update1(L, R, x, lson);
        if (R > m) update1(L, R, x, rson);
    }
    void update2(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            b[rt] = -b[rt]; 
            if (cov[rt]) cov[rt] = -cov[rt]; else rev[rt] ^= 1;
            return ;
        }
        int m = (l + r) / 2; pushdown(rt);
        if (L <= m) update2(L, R, lson);
        if (R > m) update2(L, R, rson);
    }
} f1, f2;

int ans[maxn];
void build(int l, int r, int rt) {
    if (l == r) {
        if (f1.b[rt]) ans[l] = f1.b[rt];
        else if (f2.b[rt] == 1) ans[l] = 2;
        else ans[l] = 0;
        return ;
    }
    int m = (l + r) / 2; 
    f1.pushdown(rt); f2.pushdown(rt);
    build(lson); build(rson);
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    f2.update1(1, maxv, -1, 1, maxv, 1);
    char op[2]; int x;
    while (q--) {
        scanf("%s%d", op, &x);
        if (op[0] == '<') {
            if (x <= 0) {
                f1.update1(-x + 1, maxv, 1, 1, maxv, 1);
            } else {
                f1.update1(x, maxv, 1, 1, maxv, 1);
                if (x == 1) continue;
                f1.update2(1, x - 1, 1, maxv, 1);
                f2.update2(1, x - 1, 1, maxv, 1);
            }
        } else if (op[0] == '>') {
            if (x >= 0) {
                f1.update1(x + 1, maxv, -1, 1, maxv, 1);
            } else {
                f1.update1(-x, maxv, -1, 1, maxv, 1);
                if (x == -1) continue;
                f1.update2(1, -x - 1, 1, maxv, 1);
                f2.update2(1, -x - 1, 1, maxv, 1);
            }
        }
    }
    build(1, maxv, 1);
    for (int i = 1; i <= n; i++) {
        int t = ans[abs(a[i])];
        if (t == 0) printf("%d ", a[i]);
        else if (t == 1) printf("%d ", abs(a[i]));
        else if (t == -1) printf("%d ", -abs(a[i]));
        else printf("%d ", -a[i]);
    }
    return 0;
}