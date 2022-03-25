#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, q, b[maxn] ,tree[maxn], a[maxn << 4], add[maxn << 4];

inline int lowbit(int x){return x & -x;}
inline void update(int i){
    while (i <= n){
        tree[i]++;
        i += lowbit(i);
    }
}
inline int query(int i){
    int s = 0;
    while (i > 0) {
        s += tree[i];
        i -= lowbit(i);
    }
    return s;
}

void pushup(int rt){ a[rt] = min(a[rt << 1], a[rt << 1 | 1]); }
void pushdown(int rt){
    if (add[rt]){
        add[rt << 1] += add[rt]; add[rt << 1 | 1] += add[rt];
        a[rt << 1] += add[rt]; a[rt << 1 | 1] += add[rt];
        add[rt] = 0;
    }
}
void build(int l, int r, int rt){
    add[rt] = 0;
    if (l == r){
        a[rt] = b[l];
        return;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}

void modify(int l, int r, int rt){
    if (l == r){
        a[rt] = b[l];
        update(l);
        return;
    }
    int m = (l + r) >> 1;
    pushdown(rt);
    if (a[rt << 1] == 0) modify(lson);
    if (a[rt << 1 | 1] == 0) modify(rson);
    pushup(rt);
}
void update(int L, int R, int l, int r, int rt){
    if (L <= l && r <= R){
        a[rt]--; add[rt]--;
        if (a[rt] == 0){
            modify(l, r, rt);
        }
        return;
    }
    int m = (l + r) >> 1;
    pushdown(rt);
    if (L <= m) update(L, R, lson);
    if (R > m) update(L, R, rson);
    pushup(rt);
}
void query(int L, int R, int l, int r, int rt){
    if (L <= l && r <= R){
        if (a[rt] == 0) modify(l, r, rt);
        return;    
    }
    int m = (l + r) >> 1;
    pushdown(rt);
    if (L <= m) query(L, R, lson);
    if (R > m) query(L, R, rson);
}

int main(){
    while (~scanf("%d%d", &n, &q)){
        for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
        ms(tree, 0); build(1, n, 1);
        char cmd[10]; int x, y;
        while (q--){
            scanf("%s%d%d", cmd, &x, &y);
            if (cmd[0] == 'a'){
                update(x, y, 1, n, 1);
            }
            else if (cmd[0] == 'q'){
                printf("%d\n", query(y) - query(x - 1));
            }
        }
    }
    return 0;
}