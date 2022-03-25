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
const int maxn = 200000 + 5;

vector<int> edge[maxn];
int n, k, key[maxn];

int dep[maxn], tin[maxn], tout[maxn], id[maxn], tot;
void dfs1(int u, int f) {
    tin[u] = ++tot; id[tot] = u;
    for (int v: edge[u]) {
        if (v == f) continue;
        dep[v] = dep[u] + 1;
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
        if (key[x]) mx[rt] = dep[x];
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

int ans = inf;
void dfs(int u, int f) {
    // dbg(u, f);
    // for (int i = 1; i <= n; i++) cout << query(i, i, 1, n, 1) << ' ';cout << endl;
    int q = query(1, n, 1, n, 1);
    if (q >= 0)
        ans = min(ans, q);
    for (int v: edge[u]) {
        if (v == f) continue;
        update(1, n, 1, 1, n, 1);
        update(tin[v], tout[v], -2, 1, n, 1);
        dfs(v, u);
        update(tin[v], tout[v], 2, 1, n, 1);
        update(1, n, -1, 1, n, 1);
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs1(1, 0);
    for (int i = 1, x; i <= k; i++) {
        scanf("%d", &x); key[x] = 1;
    }
    build(1, n, 1);
    dfs(1, 0);
    cout << ans;
    return 0;
}