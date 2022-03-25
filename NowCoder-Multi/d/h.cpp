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
#define lson l, m, ls[rt]
#define rson m + 1, r, rs[rt]
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;
const int maxh = 100000;
const double eps = 1e-10;

int n, q, h[maxn];

int tot, root[maxn], ls[maxn * 40], rs[maxn * 40];
ll cnt[maxn * 40], sum[maxn * 40], pre[maxn];
void update(int i, int pre, int l, int r, int& rt) {
    rt = ++tot; ls[rt] = ls[pre]; rs[rt] = rs[pre];
    cnt[rt] = cnt[pre] + 1; sum[rt] = sum[pre] + i;
    if (l == r) return ;
    int m = (l + r) / 2;
    if (i <= m) update(i, ls[pre], lson);
    else update(i, rs[pre], rson);
}
ll qcnt(int k, int pre, int l, int r, int rt) {
    if (l == r) return cnt[rt];
    int m = (l + r) / 2;
    if (k <= m) return qcnt(k, ls[pre], lson);
    else return cnt[rt] - cnt[pre] - (cnt[rs[rt]] - cnt[rs[pre]]) + qcnt(k, rs[pre], rson);
}
ll qsum(int k, int pre, int l, int r, int rt) {
    if (l == r) return sum[rt];
    int m = (l + r) / 2;
    if (k <= m) return qsum(k, ls[pre], lson);
    else return sum[rt] - sum[pre] - (sum[rs[rt]] - sum[rs[pre]]) + qsum(k, rs[pre], rson);
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", h + i);
        pre[i] = pre[i - 1] + h[i];
        update(h[i], root[i - 1], 0, maxh, root[i]);
    }
    int l, r, x, y;
    while (q--) {
        scanf("%d%d%d%d", &l, &r, &x, &y);
        if (x == y) {
            puts("0.0000000000"); continue;
        }
        // double target = 1.0 * (pre[r] - pre[l - 1]) * (y - x);
        // double tl = 0.0, tr = 1.0 * maxh;
        // auto check = [&](double x) -> bool {
        //     int k = int(x);
        //     ll cnt = qcnt(k, root[l - 1], 0, maxh, root[r]);
        //     ll sum = qsum(k, root[l - 1], 0, maxh, root[r]);
        //     double tot = 1.0 * sum + x * (r - l + 1 - cnt);
        //     return tot * y <= target;
        // };
        // while (tr - tl > eps) {
        //     double m = (tl + tr) / 2.0;
        //     if (check(m)) tl = m;
        //     else tr = m;
        // }
        // printf("%.10lf\n", tl);
        auto check = [&](int k) -> bool {
            ll cnt = qcnt(k, root[l - 1], 0, maxh, root[r]);
            ll sum = qsum(k, root[l - 1], 0, maxh, root[r]);
            ll tot = 1ll * sum + 1ll * k * (r - l + 1 - cnt);
            return tot * y <= 1ll * (pre[r] - pre[l - 1]) * (y - x);
            // return sum * y <= 1ll * (pre[r] - pre[l - 1]) * (y - x);
        };
        int tl = 0, tr = maxh, ans = 0;
        while (tl <= tr) {
            int m = (tl + tr) / 2;
            if (check(m)) ans = m, tl = m + 1;
            else tr = m - 1;
        }
        ll sum = qsum(ans, root[l - 1], 0, maxh, root[r]);
        ll cnt = qcnt(ans, root[l - 1], 0, maxh, root[r]);
        ll rest = 1ll * (pre[r] - pre[l - 1]) * (y - x) - sum * y;
        // dbg(ans, sum, cnt, rest / double(y));
        printf("%.10lf\n", (double)rest / (double(y) * double(r - l + 1 - cnt)));
        // if (cnt < r - l + 1) printf("%.10lf\n", 1.0 * ans + rest / double(r - l + 1 - cnt));
        // else printf("%.10lf\n", 1.0 * ans);
    }
    return 0;
}