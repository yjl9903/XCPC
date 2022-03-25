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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int mod = 998244353;
const int inf = 2147483647; 
const int maxn = 200000 + 50;

int tr[maxn];
inline int lowbit(int x) { return x & -x; }
inline void update(int i, int x) {
    while (i < maxn) tr[i] = max(tr[i], x), i += lowbit(i);
}
inline void del(int i) {
    while (i < maxn) tr[i] = 0, i += lowbit(i);
}
inline int query(int i) {
    int r = 0; while (i > 0) r = max(tr[i], r), i -= lowbit(i);
    return r;
}

struct edge {
    int to, nxt, d;
} g[maxn << 1];
int head[maxn], tot;
void add(int u, int v, int w) {
    g[++tot] = (edge){v, head[u], w}; head[u] = tot;
}

int n, k, m, key[maxn], ans;

int vis[maxn], siz[maxn], sum, mn, rt;
void getrt(int u, int f) {
    siz[u] = 1; int t = 0;
    for (int i = head[u]; i; i = g[i].nxt) {
        int v = g[i].to;
        if (v == f || vis[v]) continue;
        getrt(v, u); siz[u] += siz[v];
        t = max(t, siz[v]);
    }
    t = max(t, sum - siz[u]);
    if (t < mn) mn = t, rt = u;
}
int getrt(int u) {
    sum = siz[u]; mn = 1e9; rt = 0;
    getrt(u, 0); return rt;
}

int a[maxn], tmp[maxn], dep[maxn], maxd, dis[maxn];
void getdep(int u, int f) {
    maxd = max(maxd, dep[u]);
    for (int i = head[u]; i; i = g[i].nxt) {
        int v = g[i].to; 
        if (v == f || vis[v]) continue;
        dis[v] = dis[u] + g[i].d; 
        dep[v] = dep[u] + key[v];
        getdep(v, u);
    }
}
void dfs(int u, int f) {
    tmp[dep[u]] = max(tmp[dep[u]], dis[u]);
    for (int i = head[u]; i; i = g[i].nxt) {
        int v = g[i].to; 
        if (v == f || vis[v]) continue;
        dfs(v, u);
    }
}
void solve(int u) {
    vis[u] = 1; vector<PII> vec;
    if (key[u]) k--;
    for (int i = head[u]; i; i = g[i].nxt) {
        int v = g[i].to;
        if (vis[v]) continue;
        maxd = 0; dis[v] = g[i].d; dep[v] = key[v];
        getdep(v, u);
        vec.push_back({maxd, v});
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); i++) {
        int v = vec[i].second;
        // dbg(u, v, vec[i].first);
        dfs(v, u);
        if (i) {
            int l = 0, last = vec[i - 1].first, tot = vec[i].first;
            for (int i = tot; i >= 0; i--) {
                while (l + i < k && l < last) {
                    l++; a[l] = max(a[l], a[l - 1]);
                }
                if (l + i <= k) {
                    ans = max(ans, a[l] + tmp[i]);
                }
            }
        }
        if (i + 1 == (int)vec.size()) {
            for (int j = 0; j <= vec[i].first; j++) {
                if (j <= k) ans = max(ans, max(a[j], tmp[j]));
                a[j] = tmp[j] = 0;
            }
        } else {
            for (int j = 0; j <= vec[i].first; j++) {
                a[j] = max(a[j], tmp[j]); tmp[j] = 0;
            }
        }
    }
    if (key[u]) k++;
    for (int i = head[u]; i; i = g[i].nxt) {
        int v = g[i].to;
        if (vis[v]) continue;
        solve(getrt(v));
    }
}

int main() {
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 1, x; i <= m; i++) scanf("%d", &x), key[x] = 1;
    for (int i = 2, u, v, w; i <= n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w); add(v, u, w);
    }
    siz[1] = n; solve(getrt(1));
    cout << ans << endl;
    return 0;
}