#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
typedef long long LL;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

int n, m;

int ll[maxn << 2], rr[maxn << 2], tagl[maxn << 2], tagr[maxn << 2], chk[maxn << 2];
void pushdown(int rt) {
    int l = tagl[rt], r = tagr[rt];
    if (tagl[rt]) {
        if (l < ll[rt << 1]) {
            ll[rt << 1] = tagl[rt << 1] = l;
        }
        if (l < ll[rt << 1 | 1]) {
           ll[rt << 1 | 1] = tagl[rt << 1 | 1] = l;
        }
    }
    if (tagr[rt]) {
        if (r > rr[rt << 1]) {
            rr[rt << 1] = tagr[rt << 1] = r; 
        }
        if (r > rr[rt << 1 | 1]) {
            rr[rt << 1 | 1] = tagr[rt << 1 | 1] = r; 
        }
    }
    tagl[rt] = tagr[rt] = 0;
}
void pushup(int rt) {
    ll[rt] = min(ll[rt << 1], ll[rt << 1 | 1]);
    rr[rt] = max(rr[rt << 1], rr[rt << 1 | 1]);
}
void build(int l, int r, int rt) {
    tagl[rt] = tagr[rt] = chk[rt] = 0;
    ll[rt] = n + 1; rr[rt] = 0;
    if (l == r) {
        chk[rt] = 1;
        ll[rt] = rr[rt] = l; return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
    // pushup(rt);
}
void update(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) {
        if (L < ll[rt]) {
            ll[rt] = tagl[rt] = L;
        }
        if (R > rr[rt]) {
            rr[rt] = tagr[rt] = R;
        }
        return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update(L, R, lson);
    if (R > m) update(L, R, rson);
    // pushup(rt);
}
LL query(int L, int R, int l, int r, int rt) {
    if (l == r) {
        // dbg(l, r, ll[rt], rr[rt]);
        return max(R - rr[rt], 0) + max(ll[rt] - L, 0);
    }
    if (R <= rr[rt] && L >= ll[rt]) return 0;
    int m = (l + r) / 2; 
    // dbg(l, r, ll[rt], rr[rt], tagl[rt], tagr[rt]);
    pushdown(rt);
    LL ans = 0;
    if (L <= m) ans += query(L, R, lson);
    if (R > m) ans += query(L, R, rson);
    return ans;
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        build(1, n, 1);
        for (int i = 1, l, r; i <= m; i++) {
            scanf("%d%d", &l, &r);
            LL sum = query(l, r, 1, n, 1);
            printf("%lld\n", sum / 2ll);
            update(l, r, 1, n, 1);
        }
        // puts("?");
    }
    return 0;
}