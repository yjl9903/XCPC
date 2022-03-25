#include <cstdio>
#include <algorithm>
#include <cstring>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
const int maxn = 100000 + 5;

// sum 节点, add 懒惰， a 原数组
int sum[maxn << 2], add[maxn << 2], a[maxn], n;
void pushup(int rt){sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];}
void pushdown(int rt, int ln, int rn){
    if (add[rt]){
        add[rt << 1] += add[rt]; add[rt << 1 | 1] += add[rt];
        sum[rt << 1] = add[rt] * ln; sum[rt << 1 | 1] = add[rt] * rn;
        add[rt] = 0;
    }
}
void build(int l, int r, int rt){
    if (l == r){
        sum[rt] = a[l];
        return;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int i, int x, int l, int r, int rt){
    if (l == r){
        sum[rt] += x;
        return;
    }
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    pushup(rt);
}
void update(int L, int R, int x, int l, int r, int rt){
    if (L <= l && r <= R){
        sum[rt] += x * (r - l + 1);
        add[rt] += x;
        return;
    }
    int m = (l + r) >> 1;
    pushdown(rt, m - l + 1, r - m);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
}
int query(int i, int l, int r, int rt){
    if (l == r){
        return sum[rt];
    }
    int m = (l + r) >> 1;
    if (i <= l) return query(i, lson);
    return query(i, rson);
}
int query(int L, int R, int l, int r, int rt){
    if (L <= l && r <= R){
        return sum[rt];
    }
    int m = (l + r) >> 1;
    pushdown(rt, m - l + 1, r - m);
    int ans = 0;
    if (L <= m) ans += query(L, R, lson);
    if (R > m) ans += query(L, R, rson);
    return ans;
}

int main(){
    
    return 0;
}