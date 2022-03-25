#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>
#include <queue>
#include <cassert>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
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
const int maxn = 500000 + 5;

struct BIT {
    int a[maxn];
    inline int lowbit(int x) {
        return x & -x;
    }
    inline void update(int i, int x) {
        for (; i < maxn; i += lowbit(i)) a[i] += x;
    }
    inline int query(int i) {
        int r = 0;
        for (; i; i -= lowbit(i)) r += a[i];
        return r;
    }
} f;

int n, a[maxn], p[maxn], c[maxn];
vector<int> edge[maxn];

int dep[maxn], mxd;
vector<int> bag[maxn];
void dfs(int u, int f) {
    dep[u] = dep[f] + 1; mxd = max(dep[u], mxd);
    bag[dep[u]].push_back(u);
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs(v, u);
    }
}

vector<int> task;
int mn[maxn << 2], mx[maxn << 2], cnt[maxn << 2], tag[maxn << 2];
void pushup(int rt) {
    mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
    cnt[rt] = cnt[rt << 1] + cnt[rt << 1 | 1];
}
void pushdown(int rt) {
    if (tag[rt] == 0) return;
    int t = tag[rt];
    mn[rt << 1] -= t; mx[rt << 1] -= t; tag[rt << 1] -= t;
    mn[rt << 1 | 1] -= t; mx[rt << 1 | 1] -= t; tag[rt << 1 | 1] -= t;
    tag[rt] = 0;
}
void build(int l, int r, int rt) {
    if (l == r) {
        mn[rt] = mx[rt] = c[l];
        if (c[l] == 0) cnt[rt] = 1;
        return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, int l, int r, int rt) {
    if (mx[rt] == 0) return ;
    if (cnt[rt] == r - l + 1) return ;
    if (L <= l && r <= R && mn[rt] > 0) {
        mn[rt]--; mx[rt]--; tag[rt]++; return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update(L, R, lson);
    if (R > m) update(L, R, rson);
    pushup(rt);
}
void query(int L, int R, int l, int r, int rt) {
    if (mn[rt] > 0) return ;
    if (cnt[rt] == r - l + 1) return ;
    if (L <= l && r <= R) {
        if (mx[rt] == 0) {
            // dbg(l, r, cnt[rt]);
            if (cnt[rt] == 0) {
                for (int i = l; i <= r; i++) task.push_back(i);
                cnt[rt] = r - l + 1; return ;
            }
        }
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) query(L, R, lson);
    if (R > m) query(L, R, rson);
    pushup(rt);
}

int main() {
    scanf("%d", &n);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    dfs(1, 0);
    for (int i = n; i >= 1; i--) p[i] = i;
    sort(p + 1, p + 1 + n, [](int a, int b) { return dep[a] < dep[b]; });
    for (int i = 1; i <= n; i++) {
        f.update(a[p[i]] + 1, 1);
        // dbg(p[i], a[p[i]], dep[p[i]]);
        c[dep[p[i]]] = f.query(dep[p[i]]);
    }
    // for (int i = 1; i <= mxd; i++) dbg(i, c[i]);
    build(1, mxd, 1);
    priority_queue< int,vector<int>, greater<int> > pq;
    vector<int> ans;
    for (int i = 1; i <= mxd; i++) {
        if (c[i] == 0) {
            for (int& x: bag[i]) {
                pq.push(x);
            }
        }
    }
    while (!pq.empty()) {
        int x = pq.top(); pq.pop();
        ans.push_back(x);
        if (a[x] < mxd) update(a[x] + 1, mxd, 1, mxd, 1);
        query(1, mxd, 1, mxd, 1);
        for (int& x: task) {
            for (int& y: bag[x]) {
                pq.push(y);
            }
        }
        task.clear();
    }
    assert((int)ans.size() == n);
    for (int i = 0; i < n; i++) {
        if (i) putchar(' ');
        printf("%d", ans[i]);
    }
    return 0;
}