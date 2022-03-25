#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 50000 + 5;

struct LinearBase {
    static const int maxl = 61;
    ll a[maxl + 5];
    int cnt;
    LinearBase() { cnt = 0; ms(a, 0); }
    void clear() { cnt = 0; ms(a, 0); }
    void insert(ll x) {
        for (int i = maxl - 1; i >= 0; i--) {
            if (x & (1ll << i)) {
                if (a[i]) x ^= a[i];
                else {
                    for (int k = 0; k < i; k++) 
                        if (x & (1ll << k)) x ^= a[k];
                    for (int k = i + 1; k < maxl; k++) 
                        if (a[k] & (1ll << i)) a[k] ^= x;
                    a[i] = x; cnt++;
                    return ;
                }
            }
        }
    }
    ll qmax(int x) {
        ll res = x;
        for(int i = maxl - 1 ; i >= 0; i--) {
            if ((res ^ a[i]) > res) res ^= a[i];
        }
        return res;
    }
    void merge(const LinearBase& y) {
        for (int i = 0; i < maxl; i++) if (y.a[i]) insert(y.a[i]);
    }
} lb[maxn << 2], ans;

int n, q; ll a[maxn];

void build(int l, int r, int rt) {
    if (l == r) {
        lb[rt].insert(a[l]); return ;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    lb[rt] = lb[rt << 1];
    lb[rt].merge(lb[rt << 1 | 1]);
}
void query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) {
        ans.merge(lb[rt]); return ;
    }
    int m = (l + r) >> 1;
    if (L <= m) query(L, R, lson);
    if (R > m) query(L, R, rson);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%lld", a + i);
        build(1, n, 1);
        scanf("%d", &q);
        int l, r;
        while (q--) {
            scanf("%d%d", &l, &r);
            ans.clear();
            query(l, r, 1, n, 1);
            printf("%lld\n", ans.qmax(0));
        }
    }
    return 0;
}