#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, q, a[maxn], cnt, root[maxn], tree[maxn * 40], ls[maxn * 40], rs[maxn * 40];

inline int getInt(){
    char ch = getchar(); int x = 0;
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x;
}

inline void build(int l, int r, int& rt){
    rt = ++cnt; tree[rt] = 0;
    if (l == r) return;
    int m = (l + r) >> 1;
    build(lson); build(rson);
}
inline void update(int i, int x, int pre, int l, int r, int& rt){
    rt = ++cnt; ls[rt] = ls[pre]; rs[rt] = rs[pre]; tree[rt] = tree[pre] + x;
    if (l == r) return;
    int m = (l + r) >> 1;
    if (i <= m) update(i, x, ls[pre], lson);
    else update(i, x, rs[pre], rson);
}
inline int query(int x, int pre, int l, int r, int rt){
    if (l == r) return l;
    int m = (l + r) >> 1, s = tree[rs[rt]] - tree[rs[pre]] + x;
    if (m >= s) return query(s, ls[pre], lson);
    else return query(x, rs[pre], rson);
}

int main(){
    while (~scanf("%d%d", &n, &q)){
        for (int i = 1; i <= n; i++) 
            scanf("%d", &a[i]);
        cnt = 0; 
        // build(1, n, root[0]);
        for (int i = 1; i <= n; i++) update(a[i], 1, root[i - 1], 1, n, root[i]);
        while (q--){
            int l, r; 
            scanf("%d%d", &l, &r);
            printf("%d\n", query(0, root[l - 1], 1, n, root[r]));
        }
    }
    return 0;
}