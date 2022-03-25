#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

ll a[maxn], tree[2][maxn << 2];
int n, q;

void pushup(int rt){
    tree[0][rt] = tree[0][rt << 1] + tree[0][rt << 1 | 1];
    tree[1][rt] = tree[1][rt << 1] + tree[1][rt << 1 | 1];
}
void build(int l, int r, int rt){
    if (l == r){
        tree[0][rt] = a[l];
        tree[1][rt] = 1ll * (n - l + 1) * a[l];
        return;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int k, int x, int l, int r, int rt){
    if (l == r){
        tree[0][rt] = x;
        tree[1][rt] = 1ll * (n - k + 1) * x;
        return;
    }
    int m = (l + r) >> 1;
    if (k <= m) update(k, x, lson);
    else update(k, x, rson);
    pushup(rt);
}
ll query(int t, int L, int R, int l, int r, int rt){
    if (L <= l && r <= R){
        return tree[t][rt];
    }
    int m = (l + r) >> 1;
    ll ans = 0;
    if (L <= m) ans += query(t, L, R, lson);
    if (R > m) ans += query(t, L, R, rson);
    return ans;
}

int main(){
    while (~scanf("%d%d", &n, &q)){
        for (int i = 1; i <= n; i++) scanf("%lld", a + i);
        build(1, n, 1);
        int cmd, x, y;
        while (q--){
            scanf("%d%d%d", &cmd, &x, &y);
            if (cmd == 1){
                ll ans = query(1, x, y, 1, n, 1);
                ll k = query(0, x, y, 1, n, 1);
                printf("%lld\n", ans - k * (n - y));
            }
            else {
                update(x, y, 1, n, 1);
            }
        }
    }
    return 0;
}