#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <bitset>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 400000 + 5;

ll qpow(ll x, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n & 1) r = r * x % mod;
        n >>= 1; x = x * x % mod;
    }
    return r;
}

// 0~61
int pri[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293};
int inv[62];
bitset<65> fac[305];
void init() {
    for (int i = 0; i < 62; i++) inv[i] = qpow(pri[i], mod - 2);
    for (int i = 2; i <= 300; i++) {
        for (int j = 0; j < 62; j++) {
            if (i % pri[j] == 0) fac[i].set(j);
        }
    }
}

int n, q, a[maxn];

ll tr[maxn << 2], tag[maxn << 2]; bitset<65> hp[maxn << 2], ptag[maxn << 2], tot;
void pushup(int rt) {
    tr[rt] = tr[rt << 1] * tr[rt << 1 | 1] % mod;
    hp[rt] = hp[rt << 1] | hp[rt << 1 | 1];
}
void pushdown(int rt, int ln, int rn) {
    if (tag[rt] == 1) return;
    ll t = tag[rt], a = qpow(t, ln), b = qpow(t, rn);
    tr[rt << 1] = tr[rt << 1] * a % mod;
    tr[rt << 1 | 1] = tr[rt << 1 | 1] * b % mod;
    tag[rt << 1] = tag[rt << 1] * t % mod;
    tag[rt << 1 | 1] = tag[rt << 1 | 1] * t % mod;
    hp[rt << 1] |= ptag[rt];
    hp[rt << 1 | 1] |= ptag[rt];
    ptag[rt << 1] |= ptag[rt];
    ptag[rt << 1 | 1] |= ptag[rt];
    ptag[rt].reset();
    tag[rt] = 1;
}
void build(int l, int r, int rt) {
    tag[rt] = 1;
    if (l == r) {
        tr[rt] = a[l]; hp[rt] = fac[a[l]];
        return ;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, int x, int l, int r, int rt) {
    if (L <= l && r <= R) {
        tr[rt] = tr[rt] * qpow(x, r - l + 1) % mod;
        // dbg(l, r, tr[rt]);
        tag[rt] = tag[rt] * x % mod;
        hp[rt] |= fac[x]; ptag[rt] |= fac[x];
        return ;
    }
    int m = (l + r) >> 1; pushdown(rt, m - l + 1, r - m);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
}
ll query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) return tot |= hp[rt], tr[rt];
    int m = (l + r) >> 1; pushdown(rt, m - l + 1, r - m);
    ll ans = 1;
    if (L <= m) ans = query(L, R, lson);
    if (R > m) ans = ans * query(L, R, rson) % mod;
    return ans;
}

int main() {
    init();
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    build(1, n, 1);
    char op[10]; int l, r, x;
    while (q--) {
        scanf("%s%d%d", op, &l, &r);
        if (op[0] == 'M') {
            scanf("%d", &x); if (x == 1) continue;
            update(l, r, x, 1, n, 1);
        }
        if (op[0] == 'T') {
            tot.reset();
            ll ans = query(l, r, 1, n, 1);
            // cout << ans << endl << tot << endl;;
            for (int i = 0; i < 62; i++) {
                if (tot[i]) ans = ans * inv[i] % mod * (pri[i] - 1) % mod;
            }
            printf("%I64d\n", ans);
        }
    }
    return 0;
}