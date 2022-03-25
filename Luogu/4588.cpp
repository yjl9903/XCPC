#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int q; ll mod;

ll a[maxn << 2];
void build(int l, int r, int rt) {
    a[rt] = 1; if (l == r) return ;
    int m = (l + r) >> 1;
    build(lson); build(rson);
}
void update(int i, int x, int l, int r, int rt) {
    if (l == r) {
        a[rt] = x; return ;
    }
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    a[rt] = a[rt << 1] * a[rt << 1 | 1] % mod;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%lld", &q, &mod);
        build(1, q, 1);
        for (int i = 1, op, x; i <= q; i++) {
            scanf("%d%d", &op, &x);
            if (op == 1) {
                update(i, x, 1, q, 1);
            } else if (op == 2) {
                update(x, 1, 1, q, 1);
            }
            printf("%lld\n", a[1]);
        }
    }    
    return 0;
}