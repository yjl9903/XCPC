#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

vector<double> lsh;

struct Que {
    double h, l, r;
    int f;
    bool operator<(const Que& b) const {
        return h < b.h;
    }
} q[maxn];

int cnt[maxn << 2];
double len[maxn << 2];
void pushup(int rt, int l, int r) {
    if (cnt[rt]) len[rt] = lsh[r] - lsh[l - 1];
    else if (l < r) len[rt] = len[rt << 1] + len[rt << 1 | 1];
    else len[rt] = 0;
}
void update(int L, int R, int x, int l, int r, int rt) {
    if (L <= l && r <= R) {
        cnt[rt] += x;
        pushup(rt, l, r);
        dbg(l, r, len[rt]);
        return ;
    }
    int m = (l + r) / 2;
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt, l, r);
    dbg(l, r, len[rt]);
}

int n;

int main() {
    int kase = 0;
    while (scanf("%d", &n) == 1 && n) {
        lsh.clear(); ms(cnt, 0); ms(len, 0);
        for (int i = 1; i <= n; i++) {
            double x1, y1, x2, y2;
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            q[2 * i - 1] = { y1, x1, x2, 1 };
            q[2 * i] = { y2, x1, x2, -1 };
            lsh.push_back(x1);
            lsh.push_back(x2);
        }
        sort(q + 1, q + 1 + 2 * n);
        sort(lsh.begin(), lsh.end());
        lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
        double ans = 0;
        for (int i = 1; i < 2 * n; i++) {
            dbg(q[i].l, q[i].r, q[i].h);
            int l = lower_bound(lsh.begin(), lsh.end(), q[i].l) - lsh.begin() + 1;
            int r = lower_bound(lsh.begin(), lsh.end(), q[i].r) - lsh.begin();
            // dbg(lsh[l - 1], lsh[r - 1]);
            dbg(l, r, lsh.size());
            update(l, r, q[i].f, 1, (int)lsh.size(), 1);
            dbg(len[1], q[i + 1].h, q[i].h);
            ans += len[1] * (q[i + 1].h - q[i].h);
        }
        printf("Test case #%d\n", ++kase);
        printf("Total explored area: %.2f\n\n", ans);
    }
    return 0;
}