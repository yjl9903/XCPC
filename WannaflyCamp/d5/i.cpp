#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 200000 + 5;

int n, q, x, a[maxn];

int tree[maxn << 2], tag[maxn << 2];
void pushup(int rt) {
    tree[rt] = tree[rt << 1] + tree[rt << 1 | 1];
}
void pushdown(int rt, int ln, int rn) {
    if (tag[rt] == 0) {
        tree[rt << 1] = tree[rt << 1 | 1] = 0;
        tag[rt << 1] = tag[rt << 1 | 1] = 0; 
    } else if (tag[rt] == 1) {
        tree[rt << 1] = ln; tag[rt << 1] = 1;
        tree[rt << 1 | 1] = rn; tag[rt << 1 | 1] = 1;
    }
    tag[rt] = -1;
}
void build(int l, int r, int rt) {
    tag[rt] = -1;
    if (l == r) {
        tree[rt] = (a[l] > x);
        return;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, int x, int l, int r, int rt) {
    if (L <= l && r <= R) {
        tree[rt] = (r - l + 1) * x; tag[rt] = x; return;
    }
    int m = (l + r) >> 1; pushdown(rt, m - l + 1, r - m);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
}
int query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) return tree[rt];
    // dbg(l, r, rt);
    int m = (l + r) >> 1, ans = 0; pushdown(rt, m - l + 1, r - m);
    if (L <= m) ans += query(L, R, lson);
    if (R > m) ans += query(L, R, rson);
    return ans;
}

ll pre[maxn][2];

int main(){
    scanf("%d%d%d", &n, &q, &x);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    build(1, n, 1);
    int m1 = 0, m2 = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] <= x) m1++, pre[m1][0] = pre[m1 - 1][0] + a[i];
        else m2++, pre[m2][1] = pre[m2 - 1][1] + a[i];
    }
    int op, l, r;
    while (q--) {
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            int p1 = 0, p2 = query(1, r, 1, n, 1);
            if (l > 1) p1 = query(1, l - 1, 1, n, 1);
            // dbg(p2, p1, r - p2, l - 1 - p1);
            // dbg(pre[p2][1], pre[p1][1], pre[r - p2][0], pre[l - 1 - p1][0]);
            ll ans = pre[p2][1] - pre[p1][1] + pre[r - p2][0] - pre[l - 1 - p1][0];
            printf("%lld\n", ans);
        }
        if (op == 2) {
            int c = query(l, r, 1, n, 1);
            if (l <= r - c) update(l, r - c, 0, 1, n, 1);
            if (r - c + 1 <= r) update(r - c + 1, r, 1, 1, n, 1);
            // dbg(c, query(l, r, 1, n, 1));
        }
        if (op == 3) {
            int c = query(l, r, 1, n, 1);
            if (l <= l + c - 1) update(l, l + c - 1, 1, 1, n, 1);
            if (l + c <= r) update(l + c, r, 0, 1, n, 1);
            // dbg(c, query(l, r, 1, n, 1));
        }
    }
    return 0;
}