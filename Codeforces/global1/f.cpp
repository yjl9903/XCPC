#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define assert(x) do{int a=1,b=0;if(!(x))printf("%d",a/b);}while(0)
#ifdef XLor
  #define dbg(args...) do {cout << #args << " -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 998244353;
const int maxn = 500000 + 5;

vector<PII> edge[maxn];
int n, q, tot, in[maxn], out[maxn];
ll dep[maxn];

namespace init {
    void dfs(int u, ll d) {
        in[u] = ++tot; dep[u] = ((int)edge[u].size() == 0 ? d : 1e18);
        for (auto& x: edge[u]) {
            dfs(x.first, d + x.second);
        }
        out[u] = tot;
    }
}

ll tree[maxn << 2], tag[maxn << 2];
void pushup(int rt) {
    tree[rt] = min(tree[rt << 1], tree[rt << 1 | 1]);
}
void pushdown(int rt) {
    if (!tag[rt]) return;
    tree[rt << 1] += tag[rt]; tree[rt << 1 | 1] += tag[rt];
    tag[rt << 1] += tag[rt]; tag[rt << 1 | 1] += tag[rt];
    tag[rt] = 0;
}
void build(int l, int r, int rt) {
    if (l == r) {
        tree[rt] = dep[l]; return;
    }
    int m = (l + r) >> 1;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, ll x, int l, int r, int rt) {
    if (L <= l && r <= R) {
        tag[rt] += x; tree[rt] += x; return;
    }
    int m = (l + r) >> 1; pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
}
ll query(int L, int R, int l, int r, int rt) {
    if (L <= l && r <= R) return tree[rt];
    int m = (l + r) >> 1; ll ans = 1e18; pushdown(rt);
    if (L <= m) ans = min(ans, query(L, R, lson));
    if (R > m) ans = min(ans, query(L, R, rson));
    return ans;
}

int l[maxn], r[maxn];
vector<int> que[maxn];

ll allp = 0, ans[maxn];
void dfs(int u) {
    for (int& x: que[u]) {
        // dbg(u, l[x], r[x], query(l[x], r[x], 1, n, 1), allp);
        ans[x] = allp + query(l[x], r[x], 1, n, 1);
    }
    for (auto& x: edge[u]) {
        int v = x.first;
        update(in[v], out[v], -2ll * x.second, 1, n, 1);
        // dbg(in[v], out[v], x.second);
        // for (int i = 1; i <= n; i++) cout << query(i, i, 1, n, 1) << ' '; cout << endl;
        // dbg(in[v], out[v], x.second);
        allp += x.second;
        dfs(v);
        allp -= x.second;
        update(in[v], out[v], 2ll * x.second, 1, n, 1);
    }
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 2, p, d; i <= n; i++) {
        scanf("%d%d", &p, &d);
        edge[p].push_back({i, d});
    } init::dfs(1, 0); build(1, n, 1);
    // for (int i = 1; i <= n; i++) cout << query(i, i, 1, n, 1) << endl;
    for (int i = 1, x; i <= q; i++) scanf("%d%d%d", &x, l + i, r + i), que[x].push_back(i);
    dfs(1);
    for (int i = 1; i <= q; i++) printf("%I64d\n", ans[i]);
    return 0;
} 