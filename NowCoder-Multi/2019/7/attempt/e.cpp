#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxv = 1e9;
const int maxn = 400000 + 5;
const int maxm = maxn * 60;

int n, ql[maxn], qr[maxn];

int sz = 1, root = 1, ls[maxm], rs[maxm], lazy[maxm];
ll cnt[maxm];
void pushdown(int rt, int ln, int rn) {
    if (lazy[rt] == 0) return ;
    if (!ls[rt]) ls[rt] = ++sz;
    if (!rs[rt]) rs[rt] = ++sz;
    int t = lazy[rt];
    cnt[ls[rt]] += 1ll * ln * t;
    cnt[rs[rt]] += 1ll * rn * t;
    lazy[ls[rt]] += t;
    lazy[rs[rt]] += t;
    lazy[rt] = 0;
}
void update(int L, int R, int l, int r, int& rt) {
    if (!rt) rt = ++sz;
    if (L <= l && r <= R) {
        cnt[rt] += r - l + 1; lazy[rt]++;
        return ;
    }
    int m = (l + r) / 2;
    pushdown(rt, m - l + 1, r - m);
    if (L <= m) update(L, R, l, m, ls[rt]);
    if (R > m) update(L, R, m + 1, r, rs[rt]);
    cnt[rt] = cnt[ls[rt]] + cnt[rs[rt]];
}
ll query(int i, int l, int r, int rt) {
    if (!rt) return 0;
    if (l == r) return cnt[rt];
    int m = (l + r) / 2; 
    pushdown(rt, m - l + 1, r - m);
    if (i <= m) return query(i, l, m, ls[rt]);
    else return cnt[rt] - cnt[rs[rt]] + query(i, m + 1, r, rs[rt]);
}

int main() {
    scanf("%d", &n);
    int x1, x2, a1, b1, c1, m1;
    int y1, y2, a2, b2, c2, m2;
    scanf("%d%d%d%d%d%d", &x1, &x2, &a1, &b1, &c1, &m1);
    scanf("%d%d%d%d%d%d", &y1, &y2, &a2, &b2, &c2, &m2);
    ql[1] = min(x1, y1) + 1;
    qr[1] = max(x1, y1) + 1;
    ql[2] = min(x2, y2) + 1;
    qr[2] = max(x2, y2) + 1;
    for (int i = 3; i <= n; i++) {
        int nx = (1ll * a1 * x2 + 1ll * b1 * x1 + c1) % m1;
        int ny = (1ll * a2 * y2 + 1ll * b2 * y1 + c2) % m2;
        ql[i] = min(nx, ny) + 1;
        qr[i] = max(nx, ny) + 1;
        x1 = x2; x2 = nx;
        y1 = y2; y2 = ny;
    }
    ll all = 0;
    for (int i = 1; i <= n; i++) {
        // dbg(ql[i], qr[i]);
        update(ql[i], qr[i], 1, maxv, root);
        all += qr[i] - ql[i] + 1;
        ll target = (all + 1ll) / 2ll;
        int l = 1, r = maxv, ans = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            // if (check(m)) ans = m, 
            if (query(m, 1, maxv, 1) < target) ans = m + 1, l = m + 1;
            else r = m - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}