#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
#include <map>
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
const int maxn = 100000 + 5;

int n, c, k, a[maxn], last[maxn], vis[maxn];
vector<int> bag[maxn];

int tag[maxn << 2], mx[maxn << 2];
void update(int rt, int x) {
    mx[rt] += x; tag[rt] += x;
}
void pushup(int rt) {
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
}
void pushdown(int rt) {
    if (not tag[rt]) return ;
    update(rt << 1, tag[rt]);
    update(rt << 1 | 1, tag[rt]);
    tag[rt] = 0;
}
void build(int l, int r, int rt) {
    tag[rt] = mx[rt] = 0;
    if (l == r) return ;
    int m = (l + r) / 2;
    build(lson); build(rson);
}
void update(int L, int R, int x, int l, int r, int rt) {
    if (L > R) return ;
    if (L <= l and r <= R) {
        update(rt, x); return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
}
int query(int l, int r, int rt) {
    if (l == r) return l;
    int m = (l + r) / 2;
    pushdown(rt);
    if (mx[rt << 1] == c) return query(lson);
    if (mx[rt << 1 | 1] == c) return query(rson);
    return n + 1;
}

int main() {
    while (scanf("%d%d%d", &n, &c, &k) == 3) {
        for (int i = 1; i <= c; i++) {
            bag[i].clear(); bag[i].push_back(0);
        }
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
        }
        if (k == 1) {
            printf("%d\n", n); continue;
        }
        int ans = 0;
        build(1, n, 1);
        for (int i = 1; i <= n; i++) {
            update(i, i, c - 1, 1, n, 1);
            update(bag[a[i]].back() + 1, i - 1, -1, 1, n, 1);
            bag[a[i]].push_back(i);
            int pos = (int)bag[a[i]].size() - k - 1;
            if (pos >= 0) {
                update(bag[a[i]][pos] + 1, bag[a[i]][pos + 1], 1, 1, n, 1);
            }
            int l = query(1, n, 1);
            if (l <= n) ans = max(ans, i - l + 1);
        }
        printf("%d\n", ans);
    }
    return 0;
}