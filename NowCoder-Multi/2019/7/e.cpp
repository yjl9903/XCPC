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
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxv = 1e9;
const int maxn = 400000 + 5;
const int maxm = maxn * 8;

int n, nn, ql[maxn], qr[maxn];
vector<int> lsh;

ll tag[maxm], sum[maxm];
void pushdown(int rt, int l, int m, int r) {
    if (!tag[rt]) return ;
    ll t = tag[rt];
    sum[rt << 1] += t * (lsh[m] - lsh[l - 1] + 1);
    tag[rt << 1] += t;
    sum[rt << 1 | 1] += t * (lsh[r] - lsh[m] + 1);
    tag[rt << 1 | 1] += t;
    tag[rt] = 0;
}
void update(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) {
        sum[rt] += lsh[r] - lsh[l - 1] + 1;
        tag[rt] += lsh[r] - lsh[l - 1] + 1;
        return ;
    }
    int m = (l + r) / 2;
    pushdown(rt, l, m, r);
    if (L <= m) update(L, R, lson);
    if (R > m) update(L, R, rson);
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
int query(ll k, int l, int r, int rt) {
    if (l == r) {

    }
    int m = (l + r) / 2;
    if (k > sum[rt << 1]) return query(k - sum[rt << 1], rson);
    else return query(k, lson);
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
    for (int i = 1; i <= n; i++) {
        lsh.push_back(ql[i]);
        lsh.push_back(qr[i]);
    }
    lsh.push_back(maxv + 1);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nn = (int)lsh.size();
    for (int i = 1; i <= n; i++) {
        ql[i] = lower_bound(lsh.begin(), lsh.end(), ql[i]) - lsh.begin() + 1;
        qr[i] = lower_bound(lsh.begin(), lsh.end(), qr[i]) - lsh.begin() + 1;
    }
    ll all = 0;
    for (int i = 1; i <= n; i++) {
        // dbg(ql[i], qr[i]);
        update(ql[i], qr[i], 1, nn, 1);
        all += qr[i] - ql[i] + 1;
        ll target = (all + 1ll) / 2ll;
        // int l = 1, r = maxv, ans = -1;
        // while (l <= r) {
        //     int m = (l + r) / 2;
        //     if (query(m, 1, maxv, 1) < target) ans = m + 1, l = m + 1;
        //     else r = m - 1;
        // }
        // printf("%d\n", ans);
    }
    return 0;
}