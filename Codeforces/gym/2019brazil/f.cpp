#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
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
const int maxn = 10000 + 5;
const int maxv = 100000 + 5;

int n, p, lx, ly, rx, ry;
int x1[maxn], y1[maxn], x2[maxn], y2[maxn];

struct Node {
    int l, r, pos, sgn;
    bool operator<(const Node& b) const {
        return pos < b.pos;
    }
};

int cnt[maxv << 2], len[maxv << 2];
void upd(int rt, int l, int r) {
    if (cnt[rt]) len[rt] = r - l + 1;
    else if (l < r) len[rt] = len[rt << 1] + len[rt << 1 | 1];
    else len[rt] = 0;
}
void update(int L, int R, int x, int l = 0, int r = 1e5, int rt = 1) {
    if (L <= l && r <= R) {
        cnt[rt] += x; upd(rt, l, r);
        return ;
    }
    int m = (l + r) / 2;
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    upd(rt, l, r);
}

int check(int r) {
    ms(cnt, 0); ms(len, 0);
    vector<Node> upd;
    for (int i = 1; i <= n; i++) {
        int L = max(x1[i] - r, lx), R = min(x2[i] + r, rx);
        int D = max(y1[i] - r, ly), U = min(y2[i] + r, ry);
        upd.push_back({L, R, D, 1});
        upd.push_back({L, R, U, -1});
    }
    sort(upd.begin(), upd.end());
    ll ans = 0;
    for (int i = 0; i + 1 < (int)upd.size(); i++) {
        update(upd[i].l + 1, upd[i].r, upd[i].sgn);
        ans += 1ll * len[1] * (upd[i + 1].pos - upd[i].pos);
    }
    return 100ll * ans >= 1ll * p * (rx - lx) * (ry - ly);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", x1 + i, y1 + i, x2 + i, y2 + i);
    }
    scanf("%d%d%d%d%d", &p, &lx, &ly, &rx, &ry);
    int l = 1, r = 1e5, ans = r;
    while (l <= r) {
        int m = (l + r) / 2;
        if (check(m)) r = m - 1, ans = m;
        else l = m + 1;
    }
    cout << ans;
    return 0;
}