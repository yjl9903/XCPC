#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <utility>
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
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 50000 + 5;

vector<PII> edge[maxn];
int n, m, key[maxn];

int tot, tin[maxn], tout[maxn];
void dfs1(int u, int f) {
    tin[u] = ++tot;
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f) continue;
        dfs1(v, u);
    }
    tout[u] = tot;
}

int a[maxn << 2], tag[maxn << 2];
void pushup(int rt) {
    a[rt] = a[rt << 1] + a[rt << 1 | 1];
}
void pushdown(int rt) {
    if (!tag[rt]) return ;
    a[rt << 1] = 0; a[rt << 1 | 1] = 0;
    tag[rt << 1] = 1; tag[rt << 1 | 1] = 1;
    tag[rt] = 0;
}
void build(int l, int r, int rt) {
    a[rt] = tag[rt] = 0;
    if (l == r) {
        if ((int)edge[l].size() == 1) a[rt] = 1;
        return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
    pushup(rt);
}
void update(int L, int R, int l, int r, int rt) {
    if (!a[rt]) return ;
    if (L <= l && r <= R) {
        a[rt] = 0; tag[rt] = 1; return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update(L, R, lson);
    if (R > m) update(L, R, rson);
    pushup(rt);
}
int query(int L, int R, int l, int r, int rt) {
    if (!a[rt]) return 0;
    if (L <= l && r <= R) return a[rt];
    int m = (l + r) / 2, ans = 0; pushdown(rt);
    if (L <= m) ans += query(L, R, lson);
    if (R > m) ans += query(L, R, rson);
    return ans;
}

vector<int> vec;
multiset<ll> st;
ll dis[maxn], mx;
int get() {
    int l = 0, r = (int)vec.size() - 1, ans = vec.back(), u = vec.back();
    while (l <= r) {
        int m = (l + r) / 2;
        if (dis[u] - dis[vec[m]] <= mx) ans = vec[m], r = m - 1;
        else l = m + 1;
    }
    return ans;
}
void dfs(int u, int f) {
    vec.push_back(u);
    for (auto& x: edge[u]) {
        int v = x.first;
        if (v == f) continue;
        dis[v] = dis[u] + x.second;
        dfs(v, u);
    }
    if (key[u]) {
        int r = get();
        if (r == 1) {
            int c = key[u];
            if (u != 1 && query(tin[vec[1]], tout[vec[1]], 1, n, 1)) {
                c--; update(tin[vec[1]], tout[vec[1]], 1, n, 1);
            }
            while (c--) {
                st.insert(mx - dis[u]);
            }
        } else update(tin[r], tout[r], 1, n, 1);
    }
    vec.pop_back();
}
bool check(ll x) {
    st.clear();
    build(1, n, 1);
    mx = x; dfs(1, 0);
    vector<PII> v;
    for (auto& x: edge[1]) {
        v.push_back(x);
    }
    sort(v.begin(), v.end(), [&](PII a, PII b) { return a.second > b.second; });
    for (auto& x: v) {
        int v = x.first, d = x.second;
        if (query(tin[v], tout[v], 1, n, 1) == 0) continue;
        auto it = st.lower_bound(d);
        if (it == st.end()) continue;
        update(tin[v], tout[v], 1, n, 1);
        st.erase(it);
    }
    return a[1] == 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 2, u, v, w; i <= n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        edge[u].push_back({v, w});
        edge[v].push_back({u, w});
    } dfs1(1, 0);
    scanf("%d", &m);
    for (int i = 1, x; i <= m; i++) {
        scanf("%d", &x); key[x]++;
    }
    ll l = 0, r = 1e14, ans = -1;
    while (l <= r) {
        ll m = (l + r) / 2;
        if (check(m)) r = m - 1, ans = m;
        else l = m + 1;
    }
    cout << ans << endl;
    return 0;
}