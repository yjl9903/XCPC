#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int maxm = 15000000 + 5;
const int maxn = 100000 + 5;

unsigned f[maxm], n, x, y, z, a[maxn << 2], b[maxn << 2], add[maxn << 2], c[maxn];
int m;

void pushup(int rt){
    a[rt] = min(a[rt << 1], a[rt << 1 | 1]);
    b[rt] = max(b[rt << 1], b[rt << 1 | 1]);
}
void pushdown(int rt){
    if (!add[rt]) return;
    add[rt << 1] += add[rt]; add[rt << 1 | 1] += add[rt];
    a[rt << 1] += add[rt]; b[rt << 1] += add[rt];
    a[rt << 1 | 1] += add[rt]; b[rt << 1 | 1] += add[rt];
    add[rt] = 0;
}
void build(int l, int r, int rt){
    if (l == r){
        a[l] = b[l] = add[rt] = 0; return;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void modify(unsigned x, int l, int r, int rt){
    if (l == r){
        if (a[rt] < x) a[rt] = x;
        c[l] = a[rt];
        return;
    }
    int m = (l + r) >> 1;
    // pushdown(rt);
    if (a[rt << 1] < x) modify(x, lson);
    if (a[rt << 1 | 1] < x) modify(x, rson);
    pushup(rt);
}
void update(int L, int R, unsigned x, int l, int r, int rt){
    if (L <= l && r <= R){
        // a[rt] += x; b[rt] += x;
        if (a[rt] < x){
            modify(x, l, r, rt);
        }
        // pushdown(rt);
        // add[rt] = x;
        return;
    }
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
}

unsigned init(){
    x = x ^ (x << 11); x = x ^ (x >> 4); 
    x = x ^ (x << 5); x = x ^ (x >> 14);
    unsigned w = x ^ (y ^ z);
    x = y; y = z; z = w;
    return z;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%u%d%u%u%u", &n, &m, &x, &y, &z);
        for (int i = 1; i <= 3 * m; i++) f[i] = init();
        build(1, n, 1); ms(c, 0);
        for (int i = 1; i <= m; i++){
            int l = (int)min(f[3 * i - 2] % n + 1u, f[3 * i - 1] % n + 1u);
            int r = (int)max(f[3 * i - 2] % n + 1u, f[3 * i - 1] % n + 1u);
            unsigned v = f[3 * i] % (1u << 30);
            update(l, r, v, 1, n, 1);
        }
        ll res = 0;
        for (unsigned i = 1; i <= n; i++) res += i ^ c[i];
        printf("%lld\n", res);
    }
    return 0;
}