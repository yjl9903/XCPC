#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, q, a[maxn], b[maxn], tree[maxn << 2], add[maxn << 2];

int getInt(){
    char ch = getchar(), s = 0;
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s;
}

void pushup(int rt){ tree[rt] = tree[rt << 1] + tree[rt << 1 | 1]; }
void pushdown(int rt, int ln, int rn){
    if (add[rt]){
        add[rt << 1] += add[rt]; add[rt << 1 | 1] += add[rt];
        tree[rt << 1] += add[rt] * ln; tree[rt << 1 | 1] += add[rt] * rn;
        add[rt] = 0;
    }
}
void build(int l, int r, int rt){
    if (l == r) {
        tree[rt] = add[rt] = 0;
        return;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, int x, int l, int r, int rt){
    if (L <= l && r <= R){
        tree[rt] += x * (r - l + 1);
        add[rt] += x;
        return;
    }
    int m = (l + r) >> 1;
    pushdown(rt, m - l + 1, r - m);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
}
int query(int L, int R, int l, int r, int rt){
    if (l == r){
        return tree[rt] / b[l];
    }
    int m = (l + r) >> 1, ans = 0;
    pushdown(rt, m - l + 1, r - m);
    if (L <= m) ans += query(L, R, lson);
    if (R > m) ans += query(L, R, rson);
    return ans;
}

int main(){
    while (~scanf("%d%d", &n, &q)){
        for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
        // for (int i = 1; i <= n; i++) b[i] = getInt();
        build(1, n, 1);
        int x, y, q; char cmd[10];
        while (q--){
            scanf("%s%d%d", cmd, &x, &y);
            // scanf("%s", cmd); x = getInt(); y = getInt();
            if (cmd[0] == 'q'){
                printf("%d\n", query(x, y, 1, n, 1));
            }
            else if (cmd[0] == 'a'){
                update(x, y, 1, 1, n, 1);
            }
        }
    }
    return 0;
}