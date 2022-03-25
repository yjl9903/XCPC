#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 20000 + 5;

struct node {
    int x, y, w;
    bool operator<(const node& b) const {
        if (x == b.x) return y < b.y;
        return x < b.x;
    }
} a[maxn];

int n, nn;

namespace SegTree {
    #define lson l, m, rt << 1
    #define rson m + 1, r, rt << 1 | 1
    struct node {
        ll mx, le, ri, sum;
    } a[maxn << 2];
    node add(node a, node b) {
        node ans;
        ans.mx = max(a.mx, b.mx);
        ans.mx = max(ans.mx, a.ri + b.le);
        ans.le = max(a.le, a.sum + b.le);
        ans.ri = max(b.ri, b.sum + a.ri);
        ans.sum = a.sum + b.sum;
        return ans;
    }
    void build(int l = 1, int r = nn, int rt = 1) {
        if (l == r) {
            a[rt].le = a[rt].ri = a[rt].mx = a[rt].sum = 0;
            return ;
        }
        int m = (l + r) / 2;
        build(lson); build(rson);
        a[rt] = add(a[rt << 1], a[rt << 1 | 1]);
    }
    void update(int i, int x, int l = 1, int r = nn, int rt = 1) {
        if (l == r) {
            a[rt].mx += x;
            a[rt].le += x;
            a[rt].ri += x;
            a[rt].sum += x;
            return ;
        }
        int m = (l + r) / 2;
        if (i <= m) update(i, x, lson);
        else update(i, x, rson);
        a[rt] = add(a[rt << 1], a[rt << 1 | 1]);
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        vector<int> lsh; lsh.clear();
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].w);
            lsh.push_back(a[i].y);
        }
        sort(lsh.begin(), lsh.end());
        lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
        nn = (int)lsh.size() + 1;
        for (int i = 1; i <= n; i++) {
            a[i].y = lower_bound(lsh.begin(), lsh.end(), a[i].y) - lsh.begin() + 1;
        }
        sort(a + 1, a + 1 + n);
        ll ans = 0;
        auto uans = [&]() {
            ans = max(ans, SegTree::a[1].mx);
            ans = max(ans, SegTree::a[1].le);
            ans = max(ans, SegTree::a[1].ri);
            ans = max(ans, SegTree::a[1].sum);
        };
        for (int i = 1, i2; i <= n; i = i2) {
            SegTree::build();
            i2 = i;
            while (i2 <= n && a[i2].x == a[i].x) {
                SegTree::update(a[i2].y, a[i2].w);
                i2++;
            }
            uans();
            for (int j = i2, k; j <= n; j = k) {
                k = j;
                while (k <= n && a[k].x == a[j].x) {
                    SegTree::update(a[k].y, a[k].w);
                    k++;
                }
                uans();
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}