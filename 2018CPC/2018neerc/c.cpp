#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#ifdef XLor
  #define dbg(args...) do {cout << "debug -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

struct node{
    int l, r, c, p;
    bool operator<(const node& b)const{
        if (p != b.p) return p < b.p;
        return c > b.c;
    }
}a[maxn];

int n, k, m;

ll ans, laz[maxn << 2];
int mx[maxn << 2], mn[maxn << 2];
void pushup(int rt){
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
    mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
}
void pushdown(int rt){
    if (laz[rt]){
        int x = laz[rt], ls = rt << 1, rs = rt << 1 | 1;
        mx[ls] -= x; mx[rs] -= x;
        mn[ls] -= x; mn[rs] -= x;
        laz[ls] += x; laz[rs] += x; 
        laz[rt] = 0;
    }
}
void build(int l, int r, int rt){
    laz[rt] = 0;
    if (l == r){
        mx[rt] = mn[rt] = k;
        return;
    }
    int m = l + r >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, int c, int p, int l, int r, int rt){
    if (mx[rt] == 0) return;
    if (L <= l && r <= R){
        if (mn[rt] >= c){
            // puts("A"); dbg(l, r, rt, mn[rt], c, p);
            // sum[rt] += 1ll * c * p * (r - l + 1);
            ans += 1ll * c * p * (r - l + 1);
            mx[rt] -= c; mn[rt] -= c; laz[rt] += c;
            dbg(mx[rt], mn[rt]);
            return;
        }
        else if (l == r){
            // puts("B"); dbg(l, r, rt, mn[rt], c, p);
            c = min(c, mn[rt]);
            // dbg(l, r, mn[rt], c, p);
            // sum[rt] += 1ll * c * p;
            ans += 1ll * c * p;
            mx[rt] -= c; mn[rt] -= c;
            return;
        }
    }
    int m = l + r >> 1; 
    // dbg(l, r, laz[rt]);
    pushdown(rt);
    // dbg(mn[rt << 1], mn[rt << 1 | 1]);
    // dbg(l, m, r, mn[rt << 1], mn[rt << 1 | 1]);
    if (L <= m) update(L, R, c, p, lson);
    if (R > m) update(L, R, c, p, rson);
    pushup(rt);
}

int main(){
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 0; i < m; i++){
        scanf("%d%d%d%d", &a[i].l, &a[i].r, &a[i].c, &a[i].p);
        a[i].c = min(a[i].c, k);
    }
    sort(a, a + m); build(1, n, 1);

    // for (int i = 0; i < m; i++) {
    //     dbg(a[i].l, a[i].r, a[i].c, a[i].p);
    // }puts("");
    
    for (int i = 0; i < m; i++){
        update(a[i].l, a[i].r, a[i].c, a[i].p, 1, n, 1);
    }
    printf("%I64d\n", ans);
    return 0;
}