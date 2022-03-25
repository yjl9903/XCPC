#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, a[maxn], mex[maxn], nxt[maxn];
map<int,int> mp;

int mx[maxn << 2], tag[maxn << 2]; ll sum[maxn << 2];
void pushup(int rt) {
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void pushdown(int rt, int ln, int rn) {
    if (tag[rt] == -1) return ;
    int t = tag[rt];
    sum[rt << 1] = 1ll * ln * t;
    sum[rt << 1 | 1] = 1ll * rn * t;
    mx[rt << 1] = mx[rt << 1 | 1] = t;
    tag[rt << 1] = tag[rt << 1 | 1] = t;
    tag[rt] = -1;
}
void build(int l, int r, int rt) {
    tag[rt] = -1;
    if (l == r) {
        sum[rt] = mex[l]; 
        mx[rt] = mex[l];
        return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, int x, int l, int r, int rt) {
    if (L <= l && r <= R) {
        sum[rt] = 1ll * x * (r - l + 1); mx[rt] = tag[rt] = x;
        return ;
    }
    int m = (l + r) / 2; pushdown(rt, m - l + 1, r - m);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
}
int query(int v, int l, int r, int rt) {
    if (l == r) return l;
    int m = (l + r) / 2; pushdown(rt, m - l + 1, r - m);
    if (mx[rt << 1] > v) return query(v, lson);
    else return query(v, rson);
}

int main() {
    while (scanf("%d", &n) && n) {
        mp.clear();
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i); nxt[i] = 0;
        }
        for (int i = n; i >= 1; i--) {
            if (mp.count(a[i])) nxt[i] = mp[a[i]];
            else nxt[i] = n + 1;
            mp[a[i]] = i;
        }
        mp.clear(); int tot = 0;
        for (int i = 1; i <= n; i++) {
            mp[a[i]]++;
            while (mp.count(tot)) tot++;
            mex[i] = tot;
        }
        build(1, n, 1);
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            ans += sum[1];
            if (mx[1] > a[i]) {
                int l = query(a[i], 1, n, 1), r = nxt[i] - 1;
                if (l <= r) update(l, r, a[i], 1, n, 1);    
            }
            update(i, i, 0, 1, n, 1);
        }
        printf("%lld\n", ans);
    }
    return 0;
}