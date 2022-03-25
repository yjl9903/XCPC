#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

int a[maxn], q, n, tree[maxn << 2];

void pushup(int rt){ tree[rt] = max(tree[rt << 1], tree[rt << 1 | 1]); }
void build(int l, int r, int rt){
    if (l == r){
        tree[rt] = a[l];
        return;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int i, int x, int l, int r, int rt){
    if (l == r){
        tree[rt] = x;
        return;
    }
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    pushup(rt);
}
int query(int L, int R, int l, int r, int rt){
    if (L <= l && r <= R){
        return tree[rt];
    }
    int m = (l + r) >> 1, ans = 0;
    if (L <= m) ans = max(ans, query(L, R, lson));
    if (R > m) ans = max(ans, query(L, R, rson));
    return ans;
}

int main(){
    while (~scanf("%d%d", &n, &q)){
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        build(1, n, 1);
        char cmd[5]; int a, b;
        while (q--){
            scanf("%s", cmd); scanf("%d%d", &a, &b);
            if (cmd[0] == 'Q'){
                printf("%d\n", query(a, b, 1, n, 1));
            }
            else if (cmd[0] == 'U'){
                update(a, b, 1, n, 1);
            }
        }
    }
    return 0;
}