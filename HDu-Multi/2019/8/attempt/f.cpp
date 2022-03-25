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
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const ll inf = 1ll << 60;
const int maxn = 100000 + 5;

int n, a[maxn], b[maxn], tin[maxn], tout[maxn], tot;
ll val[maxn];
vector<int> edge[maxn];

struct SegTree {
    #define lson l, m, rt << 1
    #define rson m + 1, r, rt << 1 | 1
    ll mx[maxn << 2], tag[maxn << 2];
    void build(int l, int r, int rt) {
        tag[rt] = 0;
        if (l == r) {
            mx[rt] = val[l];
            return ;
        }
        int m = (l + r) / 2;
        build(lson); build(rson);
        mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
    }
    void push(int rt, ll x) {
        mx[rt] += x;
        tag[rt] += x;
    }
    void pushdown(int rt) {
        if (!tag[rt]) return ;
        ll x = tag[rt];
        push(rt << 1, x);
        push(rt << 1 | 1, x);
        tag[rt] = 0;
    }
    void update(int L, int R, ll x, int l, int r, int rt) {
        if (L <= l && r <= R) {
            push(rt, x); return ;
        }
        int m = (l + r) / 2; pushdown(rt);
        if (L <= m) update(L, R, x, lson);
        if (R > m) update(L, R, x, rson);
        mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
    }
} f;

ll suma, sumb, ans;
void predfs(int u, int ff) {
    tin[u] = ++tot;
    suma += a[u]; sumb += b[u];
    int deg = 0, id = tot;
    for (int v: edge[u]) {
        if (v == ff) continue;
        predfs(v, u);
        deg++;
    }
    tout[u] = tot;
    if (deg == 0) {
        val[id] = suma - sumb;
        dbg(id, val[id]);
    } else {
        val[id] = -inf;
    }
    suma -= a[u]; sumb -= b[u];
}
void dfs(int u, int ff) {
    ans = max(ans, f.mx[1]);
    // dbg(u, f.mx[1]);
    for (int v: edge[u]) {
        if (v == ff) continue;
        f.update(tin[v], tout[v], b[u] - a[u], 1, n, 1);
        if (1 < tin[v]) f.update(1, tin[v] - 1, a[v] - b[v], 1, n, 1);
        if (tout[v] < n) f.update(tout[v] + 1, n, a[v] - b[v], 1, n, 1);
        dfs(v, u);
        f.update(tin[v], tout[v], -b[u] + a[u], 1, n, 1);
        if (1 < tin[v]) f.update(1, tin[v] - 1, -a[v] + b[v], 1, n, 1);
        if (tout[v] < n) f.update(tout[v] + 1, n, -a[v] + b[v], 1, n, 1);
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        for (int i = 1; i <= n; i++) scanf("%d", b + i);
        for (int i = 1; i <= n; i++) edge[i].clear();
        for (int i = 2, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        suma = sumb = tot = 0;
        predfs(1, 0); 
        f.build(1, n, 1);
        for (int i = 1; i <= n; i++) dbg(i, val[i]);
        ans = -inf;
        dfs(1, 0);
        ll res = ans;
        // for (int i = 1; i <= n; i++) a[i] = -a[i], b[i] = -b[i];
        // f.build(1, n, 1);
        // suma = sumb = ans = tot = 0;
        // predfs(1, 0); dfs(1, 0);
        if (ans > res) res = -ans;
        printf("%lld\n", res);
    }
    return 0;
}