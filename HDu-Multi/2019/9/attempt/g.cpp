#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
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
const int maxn = 100000 + 5;

int n, vis[maxn];
vector<int> edge[maxn];

int siz[maxn], rt, mn, sum;
void getrt(int u, int f) {
    int m = -1;
    for (int v: edge[u]) {
        if (v == f || vis[v]) continue;
        getrt(v, u);
        siz[u] += siz[v];
        m = max(m, siz[v]);
    }
    m = max(m, sum - siz[u]);
    if (m < mn) mn = m, rt = u;
}
int getrt(int u) {
    mn = inf; sum = siz[u];
    getrt(u, 0); return rt;
}

int dep[maxn], lp[maxn], dia[maxn], tag[maxn];
int dfs(int u, int f) {
    int r = 0; dep[u] = lp[u] = 0;
    for (int v: edge[u]) {
        if (v == f || vis[v]) continue;
        r = max(r, dfs(v, u));
        lp[u] = max(lp[u], dep[u] + dep[v] + 1);
        dep[u] = max(dep[u], dep[v] + 1);
    }
    return max(r, lp[u]);
}
void solve(int u) {
    dbg(u);
    multiset<int> st;
    vis[u] = 1; dep[u] = 0;
    for (int v: edge[u]) {
        if (vis[v]) continue;
        dia[v] = dfs(v, u) + 1;
        dep[v]++;
        dbg(v, dep[v], dia[v]);
        st.insert(dep[v]);
    }
    for (int v: edge[u]) {
        if (vis[v]) continue;
        st.erase(st.find(dep[v]));
        auto it = st.end();
        int mx = 1;
        if (it != st.begin()) {
            it--; mx += *it;
            if (it != st.begin()) {
                it--; mx += *it;
            }
        }
        tag[dia[v]] = max(tag[dia[v]], mx);
        tag[mx] = max(tag[mx], dia[v]);
        st.insert(dep[v]);
    }
    for (int v: edge[u]) {
        if (vis[v]) continue;
        solve(getrt(v));
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            edge[i].clear(); vis[i] = tag[i] = 0;
        }
        for (int i = 2, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        int mxdia = dfs(1, 0) + 1;
        dbg(mxdia);
        siz[1] = n;
        solve(getrt(1));
        ll ans = 0;
        for (int i = mxdia; i >= 1; i--) {
            if (i < mxdia) tag[i] = max(tag[i + 1], tag[i]);
            ans += tag[i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}