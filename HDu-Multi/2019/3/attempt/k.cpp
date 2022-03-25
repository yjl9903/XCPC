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
const int maxn = 100000 + 5;

int n, dep[maxn], tin[maxn], tout[maxn], id[maxn], tot;
vector<PII> edge[maxn];

void dfs1(int u, int f) {
    tin[u] = ++tot; id[tot] = u;
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f) continue;
        dep[v] = dep[u] + x.second;
        dfs1(v, u);
    }
    tout[u] = tot;
}

int mx[maxn << 2], tag[maxn << 2];
void update(int rt, int x) {
    mx[rt] += x; tag[rt] += x;
}
void pushup(int rt) {
    mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
}
void pushdown(int rt) {
    if (!tag[rt]) return ;
    update(rt << 1, tag[rt]);
    update(rt << 1 | 1, tag[rt]);
    tag[rt] = 0;
}
void build(int l, int r, int rt) {
    mx[rt] = -inf; tag[rt] = 0;
    if (l == r) {
        int x = id[l];
        mx[rt] = dep[x];
        return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, int x, int l, int r, int rt) {
    if (L <= l && r <= R) {
        update(rt, x); return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
}
int query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) return mx[rt];
    int m = (l + r) / 2, ans = -inf; pushdown(rt);
    if (L <= m) ans = query(L, R, lson);
    if (R > m) ans = max(ans, query(L, R, rson));
    return ans;
}

int mn, pos;
void dfs(int u, int f) {
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f) continue;
        update(tin[v], tout[v], -x.second, 1, n, 1);
        int t = query(1, n, 1, n, 1);
        dbg(u, v, t);
        if (t < mn) {
            mn = t; pos = min(u, v);
        } else if (t == mn) {
            pos = min(pos, u);
            pos = min(pos, v);
        }
        update(tin[v], tout[v], -x.second, 1, n, 1);
        update(1, n, x.second, 1, n, 1);
        dfs(v, u);
        update(1, n, -x.second, 1, n, 1);
        update(tin[v], tout[v], 2 * x.second, 1, n, 1);
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) edge[i].clear();
        for (int i = 2, u, v, w; i <= n; i++) {
            scanf("%d%d%d", &u, &v, &w);
            edge[u].push_back({v, w});
            edge[v].push_back({u, w});
        }
        tot = 0; dep[1] = 0;
        dfs1(1, 0);
        build(1, n, 1);
        pos = -1; mn = inf;
        dfs(1, 0);
        printf("%d %d\n", pos, mn);
    }
    return 0;
}