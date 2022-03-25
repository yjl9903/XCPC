#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#ifdef XLor
  #define dbg(args...) do {cout << "debug -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

int n, m, a[maxn], mx[maxn << 2], cnt[maxn << 2], se[maxn << 2], add[maxn << 2];
ll sum[maxn << 2];

void pushup(int rt){
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
    if (mx[rt << 1] == mx[rt << 1 | 1]){
        se[rt] = max(se[rt << 1], se[rt << 1 | 1]);
        mx[rt] = mx[rt << 1];
        cnt[rt] = cnt[rt << 1] + cnt[rt << 1 | 1];
    }
    else if (mx[rt << 1] < mx[rt << 1 | 1]){
        se[rt] = max(mx[rt << 1], se[rt << 1 | 1]);
        mx[rt] = mx[rt << 1 | 1];
        cnt[rt] = cnt[rt << 1 | 1];
    }
    else {
        se[rt] = max(mx[rt << 1 | 1], se[rt << 1]);
        mx[rt] = mx[rt << 1];
        cnt[rt] = cnt[rt << 1];
    }
}
void pushdown(int rt){
    if (add[rt] == -1) return;
    // 区间覆盖
    int& t = add[rt]; int ls = rt << 1, rs = rt << 1 | 1;
    // sum[ls] += x * cnt[ls]; sum[rs] += x * cnt[rs];
    // add[ls] += x; add[rs] += x;
    if (mx[ls] > t && t > se[ls]) {
        sum[ls] -= 1ll * (mx[ls] - t) * cnt[ls];
        add[ls] = mx[ls] = t;
    }
    if (mx[rs] > t && t > se[rs]){
        sum[rs] -= 1ll * (mx[rs] - t) * cnt[rs];
        add[rs] = mx[rs] = t;
    }
    t = -1;
}
void build(int l, int r, int rt){
    add[rt] = -1; 
    if (l == r){
        se[rt] = -1; cnt[rt] = 1;
        sum[rt] = mx[rt] = a[l];
        return;
    }
    int m = l + r >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, int t, int l, int r, int rt){
    if (mx[rt] <= t) return;
    if (L <= l && r <= R && se[rt] < t){
        sum[rt] -= 1ll * (mx[rt] - t) * cnt[rt];
        mx[rt] = add[rt] = t; 
        return;
    }
    int m = l + r >> 1; 
    pushdown(rt);
    if (L <= m) update(L, R, t, lson);
    if (R > m) update(L, R, t, rson);
    pushup(rt);
}
int qmax(int L, int R, int l, int r, int rt){
    if (L <= l && r <= R) return mx[rt];
    int m = l + r >> 1; int ans = 0;
    pushdown(rt);
    if (L <= m) ans = max(ans, qmax(L, R, lson));
    if (R > m) ans = max(ans, qmax(L, R, rson));
    return ans;
}
ll qsum(int L, int R, int l, int r, int rt){
    if (L <= l && r <= R) return sum[rt];
    int m = l + r >> 1; ll ans = 0;
    pushdown(rt);
    if (L <= m) ans += qsum(L, R, lson);
    if (R > m) ans += qsum(L, R, rson);
    return ans;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        build(1, n, 1); int op, x, y, t;
        while (m--){
            scanf("%d", &op);
            if (op == 0){
                scanf("%d%d%d", &x, &y, &t);
                update(x, y, t, 1, n, 1);
            }
            if (op == 1){
                scanf("%d%d", &x, &y);
                printf("%d\n", qmax(x, y, 1, n, 1));
            }
            if (op == 2){
                scanf("%d%d", &x, &y);
                printf("%lld\n", qsum(x, y, 1, n, 1));
            }
        }
    }    
    return 0;
}