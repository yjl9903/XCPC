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
const double eps = 1e-7;
  
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
ll qcnt(int L, int R, int pre, int l, int r, int rt) {
    if (L <= l && r <= R) return cnt[rt] - cnt[pre];
    int m = (l + r) / 2;
    ll ans = 0;
    if (L <= m) ans += qcnt(L, R, ls[pre], lson);
    if (R > m) ans += qcnt(L, R, rs[pre], rson);
    return ans;
}
ll qsum(int L, int R, int pre, int l, int r, int rt) {
    if (L <= l && r <= R) return sum[rt] - sum[pre];
    int m = (l + r) / 2;
    ll ans = 0;
    if (L <= m) ans += qsum(L, R, ls[pre], lson);
    if (R > m) ans += qsum(L, R, rs[pre], rson);
    return ans;
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
        double s = 1.0 * (pre[r] - pre[l - 1]) * x / (double)y;
        double tl = 0, tr = maxh;
        while (tr - tl > eps) {
            double m = tl + (tr - tl) / 2;
            ll cnt = qcnt((int)ceil(m), maxh, root[l - 1], 0, maxh, root[r]);
            ll sum = qsum((int)ceil(m), maxh, root[l - 1], 0, maxh, root[r]);
            double us = sum - cnt * m;
            if (us > s) tl = m;
            else tr = m;
        }
        printf("%.8lf\n", tl);
    }
    return 0;
}