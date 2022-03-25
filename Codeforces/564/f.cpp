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
const int maxn = 400000 + 5;

ll sqr(int x) {
    return 1ll * x * x;
}

vector<int> edge[maxn];
int n, m, a[maxn], c[maxn], f[maxn];

void dfs(int u, int ff) {
    f[u] = ff;
    for (int& v: edge[u]) if (v != ff) dfs(v, u);    
}

ll res = 0;
namespace LCT {
    int fa[maxn], ch[maxn][2], rev[maxn], s[maxn], sizi[maxn]; ll siz2i[maxn];
    int nroot(int x) { return ch[fa[x]][0] == x || ch[fa[x]][1] == x; }
    int get(int x) { return ch[fa[x]][1] == x; }
    void pushup(int x) { 
        s[x] = s[ch[x][0]] + s[ch[x][1]] + 1 + sizi[x];
    }
    void rot(int x) {
        int old = fa[x], oldf = fa[old], k = get(x), w = ch[x][k ^ 1];
        if (nroot(old)) ch[oldf][ch[oldf][1] == old] = x; 
        ch[x][k ^ 1] = old; ch[old][k] = w;
        if (w) fa[w] = old; 
        fa[old] = x; fa[x] = oldf;
        pushup(old); pushup(x);
    }
    void splay(int x) {
        while (nroot(x)) {
            int y = fa[x];
            if (nroot(y)) rot(get(x) == get(y) ? y : x);
            rot(x); 
        }
        pushup(x);
    }
    void access(int x) {
        for (int y = 0; x; y = x, x = fa[x]) {
            splay(x);
            sizi[x] += s[ch[x][1]];
            sizi[x] -= s[y];
            siz2i[x] += sqr(s[ch[x][1]]);
            siz2i[x] -= sqr(s[y]);
            ch[x][1] = y;
            pushup(x);
        }
    }
    int findroot(int x) {
        access(x); splay(x);
        while (ch[x][0]) x = ch[x][0];
        splay(x); // ?
        return x;
    }
    void link(int x, int y) {
        splay(x);
        res -= siz2i[x] + sqr(s[ch[x][1]]);
        int z = findroot(y);
        access(x); splay(z);
        res -= sqr(s[ch[z][1]]);

        fa[x] = y;
        splay(y);
        sizi[y] += s[x];
        siz2i[y] += sqr(s[x]);
        pushup(y);
        access(x);
        splay(z);
        
        res += sqr(s[ch[z][1]]);
    }
    void cut(int x, int y) {
        access(x);
        res += siz2i[x];
        int z = findroot(y);
        access(x);
        splay(z);
        res -= sqr(s[ch[z][1]]);
        splay(x);

        ch[x][0] = fa[ch[x][0]] = 0;
        pushup(x);
        splay(z);
        res += sqr(s[ch[z][1]]);
    }
} using namespace LCT;

int key[maxn];
vector<PII> q[maxn];
ll d[maxn];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", c + i); q[c[i]].push_back({i, 0});
    }
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v); edge[v].push_back(u);
    } dfs(1, n + 1);
    for (int i = 1, u, x; i <= m; i++) {
        scanf("%d%d", &u, &x);
        q[c[u]].push_back({u, i});
        c[u] = x;
        q[x].push_back({u, i});
    }
    for (int i = 1; i <= n; i++) link(i, f[i]);
    for (int i = 1; i <= n; i++) {
        if (q[i].empty()) {
            d[0] += 1ll * n * n; continue;
        }
        ll last = 0;
        if (q[i].front().second) {
            d[0] += 1ll * n * n;
            last = 1ll * n * n;
        }
        for (int j = 0; j < (int)q[i].size(); j++) {
            int u = q[i][j].first;
            key[u] ^= 1;
            if (key[u]) cut(u, f[u]);
            else link(u, f[u]);
            if (j == (int)q[i].size() - 1 || q[i][j].second < q[i][j + 1].second) {
                d[q[i][j].second] += res - last;
                last = res;
            }
        }
        for (int j = (int)q[i].size() - 1; j >= 0; j--) {
            int u = q[i][j].first;
            key[u] ^= 1;
            if (key[u]) cut(u, f[u]);
            else link(u, f[u]);
        }
    }
    ll ans = 1ll * n * n * n;
    for (int i = 0; i <= m; i++) {
        ans -= d[i]; printf("%lld\n", ans);
    }
    return 0;
}