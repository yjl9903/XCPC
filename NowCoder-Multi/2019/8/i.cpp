#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 600000 + 5;

ll c[maxn], s[maxn];
inline int lowbit(int i) { return i & -i; }
inline void update(int i, int x) {
    int y = 1ll * i * x;
    for (; i < maxn; i += lowbit(i)) {
        c[i] += x; s[i] += y;
    }
}
inline void update(int l, int r, int x) {
    update(l, x); update(r + 1, -x);
}
inline ll query(ll* a, int i) {
    ll r = 0;
    for (; i; i -= lowbit(i)) r += a[i];
    return r;
}
inline ll query(int l, int r) {
    return (r - l + 1) * query(c, l - 1) + (r + 1) * (query(c, r) - query(c, l - 1)) - query(s, r) + query(s, l - 1);
}

int n, m, q, le[maxn], ri[maxn];
vector<int> edge[maxn];

int tot, dfn[maxn], rdfn[maxn], siz[maxn];
void dfs(int u) {
    dfn[u] = ++tot; rdfn[tot] = u;
    siz[u] = 1;
    for (int v: edge[u]) {
        dfs(v); siz[u] += siz[v];
    }
}

struct Query {
    int x, l, tp, id;
};
ll ans[maxn];

int main() {
    scanf("%d%d", &n, &m);
    le[1] = 1; ri[1] = n;
    for (int i = 1, u, v, l, r; i <= m; i++) {
        scanf("%d%d%d%d", &u, &v, &l, &r);
        edge[u].push_back(v);
        le[v] = l; ri[v] = r;
    }
    dfs(1);
    scanf("%d", &q);
    vector<Query> que;
    for (int i = 1, x, l, r; i <= q; i++) {
        scanf("%d%d%d", &x, &l, &r);
        que.push_back({ dfn[x] - 1, l - 1, 1, i });
        que.push_back({ dfn[x] - 1, r, -1, i });
        que.push_back({ dfn[x] + siz[x] - 1, l - 1, -1, i });
        que.push_back({ dfn[x] + siz[x] - 1, r, 1, i });
    }
    sort(que.begin(), que.end(), [&](Query a, Query b) {
        return a.x < b.x;
    });
    int j = 0, sz = (int)que.size();
    while (j < sz && que[j].x == 0) j++;
    for (int i = 1; i <= tot; i++) {
        int u = rdfn[i];
        update(le[u], ri[u], 1);
        while (j < sz && que[j].x == i) {
            ans[que[j].id] += que[j].tp * query(1, que[j].l);
            j++;
        }
    }
    for (int i = 1; i <= q; i++) printf("%lld\n", ans[i]);
    return 0;
}