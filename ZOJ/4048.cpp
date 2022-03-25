#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 200000 + 5;

int n, m, q, red[maxn], dp[maxn][30], last[maxn], v[maxn];
ll dis[maxn];

int gi(){
    int r = 0; char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') r = r * 10 + ch - '0', ch = getchar();
    return r;
}

namespace hld{
    struct edge{int to, nxt, w;}g[maxn];
    int head[maxn], tot;
    void add(int x, int y, int w){
        g[++tot] = {y, head[x], w}; head[x] = tot;
    }

    int siz[maxn], dep[maxn], fa[maxn], son[maxn], top[maxn];
    void dfs(int p, int d, int old){
        dep[p] = d; fa[p] = old; siz[p] = 1;
        int m = -1;
        for (int i = head[p]; i; i = g[i].nxt){
            int v = g[i].to;
            if (v == fa[p]) continue;
            if (red[v]) dis[v] = 0, last[v] = v;
            else dis[v] = dis[p] + 1ll * g[i].w, last[v] = last[p];
            dfs(v, d + 1, p);
            siz[p] += siz[v];
            if (siz[v] > m) son[p] = v, m = siz[v];
        }
    }
    void dfs(int p, int tp){
        top[p] = tp;
        if (!son[p]) return;
        dfs(son[p], tp);
        for (int i = head[p]; i; i = g[i].nxt){
            int v = g[i].to;
            if (v == fa[p] || v == son[p]) continue;
            dfs(v, v);
        }
    }
    void init(){
        ms(son, 0); dfs(1, 1, 0); dfs(1, 1);
    }

    int qlca(int x, int y){
        while (top[x] != top[y]){
            if (dep[top[x]] < dep[top[y]]) swap(x, y);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y]) swap(x, y);
        return x;
    }
}
using namespace hld;

int check(ll m, int c){
    int flag = 1, k = -1; ll mdis = 0;
    for (int i = 0; i < c; i++){
        int x = v[i];
        if (dis[x] > m){
            if (flag) k = x, flag = 0;
            else k = qlca(k, x);
        }
    }
    if (k == -1) return 1;
    for (int i = 0; i < c; i++) if (dis[v[i]] > m && last[k] != last[v[i]]) return 0;
    for (int i = 0; i < c; i++) if (dis[v[i]] - dis[k] > m) return 0;
    return 1;
}

int main(){
    int T; T = gi();
    while (T--){
        n = gi(); m = gi(); q = gi();
        ms(red, 0); ms(head, 0); tot = 0;
        for (int i = 0, x; i < m; i++) x = gi(), red[x] = 1;
        for (int i = 1, u, v, w; i < n; i++){
            u = gi(); v = gi(); w = gi();
            add(u, v, w); add(v, u, w);
        } init();

        while (q--){
            int nk, x; nk = gi();
            ll l = 0, r = 0, ans = 0;
            for (int i = 0, x; i < nk; i++){
                v[i] = gi(); r = max(dis[v[i]], r);
            }
            while (l <= r){
                ll m = (l + r) / 2;
                if (check(m, nk)) r = m - 1, ans = m;
                else l = m + 1;
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}