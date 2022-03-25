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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

vector<int> lsh;
int gid(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
}

struct Point {
    int x, y, c;
} a[maxn];

int n, nn;
vector<PII> row[maxn], col[maxn];
vector<int> yx[maxn];

namespace SegTree {
    #define lson l, m, rt << 1
    #define rson m + 1, r, rt << 1 | 1
    struct Info {
        ll val; int pos;
        Info operator+(const Info& b) {
            if (val > b.val) return (Info){ val, pos };
            else if (val == b.val && pos > b.pos) return (Info){ val, pos };
            else return (Info){ b.val, b.pos };
        }
    } a[maxn << 2];
    ll tag[maxn << 2];
    void pushup(int rt) {
        a[rt] = a[rt << 1] + a[rt << 1 | 1];
    }
    void update(int rt, ll x) {
        a[rt].val += x;
        tag[rt] += x;
    }
    void pushdown(int rt) {
        if (!tag[rt]) return ;
        update(rt << 1, tag[rt]);
        update(rt << 1 | 1, tag[rt]);
        tag[rt] = 0;
    }
    void build(int l = 1, int r = nn, int rt = 1) {
        if (l == r) {
            a[rt].val = 0; a[rt].pos = l;
            return ;
        }
        int m = (l + r) / 2;
        build(lson); build(rson);
        pushup(rt);
    }
    void update(int L, int R, int x, int l = 1, int r = nn, int rt = 1) {
        if (L <= l && r <= R) {
            update(rt, x); return ;
        }
        int m = (l + r) / 2; pushdown(rt);
        if (L <= m) update(L, R, x, lson);
        if (R > m) update(L, R, x, rson);
        pushup(rt);
    }
    Info query(int L, int R, int l = 1, int r = nn, int rt = 1) {
        if (L <= l && r <= R) return a[rt];
        int m = (l + r) / 2; pushdown(rt);
        if (R <= m) return query(L, R, lson);
        else if (L > m) return query(L, R, rson);
        else return query(L, R, lson) + query(L, R, rson);
    }
}
using SegTree::Info;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].c);
        lsh.push_back(a[i].x);
        lsh.push_back(a[i].y);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nn = (int)lsh.size();
    SegTree::build();

    for (int i = 1; i <= n; i++) {
        int x = gid(a[i].x);
        int y = gid(a[i].y);
        if (a[i].x > a[i].y) {
            col[x].push_back({y, a[i].c});
        } else if (a[i].x < a[i].y) {
            row[y].push_back({x, a[i].c});
        } else {
            yx[x].push_back(a[i].c);
        }
    }
    ll ans = 0; int p1 = 2e9, p2 = 2e9;
    auto merge = [&](int r, const Info& x) {
        if (x.val <= ans) return ;
        ans = x.val; 
        p1 = lsh[x.pos - 1];
        p2 = lsh[r - 1];
    };
    for (int i = 1; i <= nn; i++) {
        if (i > 1) {
            SegTree::update(1, i - 1, -(lsh[i - 1] - lsh[i - 2]));
        }
        for (auto& x: yx[i]) {
            SegTree::update(1, i, x);
        }
        for (auto& x: row[i]) {
            SegTree::update(1, x.first, x.second);
        }
        for (auto& x: col[i]) {
            SegTree::update(1, x.first, x.second);
        }
        merge(i, SegTree::query(1, i));
    }
    printf("%lld\n%d %d %d %d", ans, p1, p1, p2, p2);
    return 0;
}