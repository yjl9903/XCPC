#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

struct Fenwick {
    ll a[maxn];
    inline int lowbit(int x) { return x & -x; }
    inline void update(int i, int x) {
        while (i < maxn) a[i] += x, i += lowbit(i);
    }
    inline ll query(int i) {
        ll r = 0; while (i > 0) r += a[i], i -= lowbit(i);
        return r;
    }
} tree;

vector<int> edge[maxn];
vector<int> deps[maxn];
int n, q, tot, maxd, in[maxn], out[maxn], id[maxn], dep[maxn], depid[maxn], sumd[maxn][260];
ll tag[260];

void dfs(int u, int f, int d) {
    maxd = max(d, maxd);
    in[u] = ++tot; dep[tot] = d; id[tot] = u;
    deps[d].push_back(u);
    for (int& v: edge[u]) {
        if (v == f) continue;
        dfs(v, u, d + 1);
    }
    out[u] = tot;
}

int main(){
    scanf("%d%d", &n, &q);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v); edge[v].push_back(u);
    }
    dfs(1, 0, 0);
    int sz = 250, cntd = 0;
    vector<int> v;
    for (int i = 0; i <= maxd; i++) {
        if (deps[i].size() <= sz) depid[i] = -1;
        else {
            depid[i] = ++cntd; v.push_back(i);
        }
    }
    for (int i = 1; i <= tot; i++) {
        for (int j = 1; j <= cntd; j++) sumd[i][j] = sumd[i - 1][j];
        if (depid[dep[i]] != -1) sumd[i][depid[dep[i]]]++;
    }

    int op, x, y;
    while (q--) {
        scanf("%d%d", &op, &x);
        if (op == 1) {
            scanf("%d", &y);
            if (deps[x].size() <= sz) {
                for (int& v: deps[x]) tree.update(in[v], y);
            } else {
                tag[depid[x]] += y;
            }
        }
        else if (op == 2) {
            ll ans = tree.query(out[x]) - tree.query(in[x] - 1);
            for (int i = 1; i <= cntd; i++) {
                ans += 1ll * (sumd[out[x]][i] - sumd[in[x] - 1][i]) * tag[i];
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}