#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
using namespace std;
typedef long long ll;
const int maxn = 30000 + 5;
const int inf = 1e6 + 5;

int n, q, cnt = 0, a[maxn], vis[inf] = {0}, root[maxn], tree[maxn * 40], ls[maxn * 40], rs[maxn * 40];

void build(int l, int r, int& rt){
    rt = ++cnt;
    if (l == r){
        tree[rt] = 0; return;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
}
void update(int i, int x, int pre, int l, int r, int& rt){
    rt = ++cnt; ls[rt] = ls[pre]; rs[rt] = rs[pre]; tree[rt] = tree[pre] + x;
    if (l == r){
        return;
    }
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, ls[pre], lson);
    else update(i, x, rs[pre], rson);
}
int query(int i, int l, int r, int rt){
    if (l == i) return tree[rt];
    int m = (l + r) >> 1;
    if (i <= m) return query(i, lson) + tree[rs[rt]];
    else return query(i, rson);
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    scanf("%d", &q);
    build(1, n, root[0]);
    for (int i = 1; i <= n; i++){
        if (vis[a[i]]){
            int tmp;
            update(vis[a[i]], -1, root[i - 1], 1, n, tmp);
            update(i, 1, tmp, 1, n, root[i]);
        }
        else {
            update(i, 1, root[i - 1], 1, n, root[i]);
        }
        vis[a[i]] = i;
    }

    int x, y;
    while (q--){
        scanf("%d%d", &x, &y);
        printf("%d\n", query(x, 1, n, root[y]));
    }
    return 0;
}