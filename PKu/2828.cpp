#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int n, pos[maxn], val[maxn], ans[maxn];
int sum[maxn << 2];

void build(int l, int r, int rt){
    if (l == r) return;
    int m = (l + r) >> 1;
    build(lson); build(rson);
}
void update(int i, int x, int l, int r, int rt){
    if (l == r){
        sum[rt] += x;
        return;
    }
    int m = (l + r) >> 1;
    if (l <= m) update(i, x, lson);
    else update(i, x, rson);
}

int main(){
    while (~scanf("%d", &n)){
        ms(sum, 0); ms(ans, 0);
        build(1, n, 1);
        for (int i = 0; i < n; i++){
            scanf("%d%d", &pos[i], &val[i]);
            update(pos[i] + 1, 1, 1, n, 1);
        }

    }
    return 0;
}