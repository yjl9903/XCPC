#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <cassert>
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
const int maxn = 1000000 + 5;

inline int gi() {
    int r = 0; char c = getchar();
    while (c < '0' || c  > '9') c = getchar();
    while (c >= '0' && c <= '9')
        r = r * 10 + c - '0', c = getchar();
    return r;
}
struct edge {
    int to, nxt, w;
} g[maxn << 2];
int ecnt, head[maxn];
void adde(int u, int v, int w) {
    g[++ecnt] = { v, head[u], w }; head[u] = ecnt;
}

int n;
bool ok[maxn], vis[maxn], ring[maxn];

int fa[maxn], falen[maxn];
int onring[maxn], rlen[maxn], sz;
void getring(int u, int f) {
    int c = 1;
    fa[u] = f; vis[u] = ok[u] = 1;
    for (int i = head[u]; i; i = g[i].nxt) {
        int v = g[i].to;
        if (v == f && c) {
            c--; continue;
        }
        if (vis[v]) {
            if (sz >= 0) continue;
            int x = u;
            onring[++sz] = v;
            rlen[sz] = g[i].w;
            while (x != v) {
                onring[++sz] = x;
                rlen[sz] = falen[x];
                x = fa[x];
            }
            continue;
        }
        falen[v] = g[i].w;
        getring(v, u);
    }
    vis[u] = 0;
}
ll dep[maxn], lp[maxn], mxd, dep2[maxn], pre[maxn]; int pos;
ll dfs(int u, int f) {
    ll r = 0; dep[u] = lp[u] = 0;
    for (int i = head[u]; i; i = g[i].nxt) {
        int v = g[i].to;
        if (v == f) continue;
        if (ring[u] && ring[v]) continue;
        r = max(r, dfs(v, u)); 
        lp[u] = max(lp[u], dep[u] + dep[v] + g[i].w);
        dep[u] = max(dep[u], dep[v] + g[i].w);
    }
    return max(r, lp[u]);
}

int q[maxn];

int main() {
    n = gi();
    ll ans = 0;
    for (int i = 1, v, l; i <= n; i++) {
        v = gi(); l = gi();
        adde(i, v, l); adde(v, i, l);
    }
    for (int i = 1; i <= n; i++) if (!ok[i]) {
        sz = -1; getring(i, 0); sz++;
        ll len = 0, res = 0;
        for (int i = 0; i < sz; i++) dbg(onring[i]);
        for (int i = 0; i < sz; i++) ring[onring[i]] = 1;
        for (int i = 0; i < sz; i++) {
            int x = onring[i];
            res = max(res, dfs(x, 0));
            dep2[i] = dep2[i + sz] = dep[x];
            onring[sz + i] = onring[i];
        }
        for (int i = 0; i < 2 * sz; i++) {
            if (i) {
                if (i <= sz) len += rlen[i - 1];
                else len += rlen[i - sz - 1];
            }
            pre[i] = len;
        }
        int l = 0, r = -1;
        for (int i = 0; i < 2 * sz; i++) {
            while (l <= r && i - q[l] >= sz) l++;
            ll tot = dep2[i] + pre[i];
            if (l <= r) tot += dep2[q[l]] - pre[q[l]];
            res = max(res, tot);
            while (l <= r && dep2[q[r]] - pre[q[r]] <= dep2[i] - pre[i]) r--;
            q[++r] = i;
        }
        ans += res;
    }
    cout << ans;
    return 0;
}