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
const int maxn = 1000000 + 5;

vector<int> edge[maxn];
int n, m, r, a[maxn];

int tin[maxn], tout[maxn], tot;
void dfs(int u, int f) {
    tin[u] = ++tot;
    for (int v: edge[u]) {
        if (v == f) continue;
        dfs(v, u);
    }
    tout[u] = tot;
}

// ll b[maxn];
// inline int lowbit(int x) { return x & -x; }
// void update(int i, int x) {
//     for (; i <= n; i += lowbit(i)) b[i] += x;
// }
// ll query(int i) {
//     ll r = 0;
//     for (; i; i -= lowbit(i)) r += b[i];
//     return r;
// }
// ll query(int l, int r) {
//     return query(r) - query(l - 1);
// }
ll c[maxn], s[maxn];
inline int lowbit(int i) { return i & -i; }
inline void update(int i, int x) {
    ll y = 1ll * i * x;
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

int main() {
    scanf("%d%d%d", &n, &m, &r);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v); edge[v].push_back(u);
    } dfs(r, 0);
    for (int i = 1; i <= n; i++) update(tin[i], tin[i], a[i]);
    int op, p, x;
    while (m--) {
        scanf("%d%d", &op, &p);
        if (op == 1) {
            scanf("%d", &x);
            // update(tin[p], x);
            update(tin[p], tout[p], x);
        } else {
            printf("%lld\n", query(tin[p], tout[p]));
        }
    }
    return 0;
}