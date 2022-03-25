#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
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
const ll inf = 1ll << 60;
const int maxn = 100000 + 5;

struct Info {
    ll mx, mx2;
    void clear() {
        mx = mx2 = -inf;
    }
    void insert(ll x) {
        if (x >= mx) mx2 = mx, mx = x;
        else if (x > mx2) mx2 = x;
    }
    ll get(ll x) {
        ll ans = 0;
        if (x == mx) ans = mx2;
        else ans = mx;
        return ans == -inf ? 0 : ans;
    }
} c[maxn];
struct Info2 {
    ll mn, mn2;
    void clear() {
        mn = mn2 = inf;
    }
    void insert(ll x) {
        if (x <= mn) mn2 = mn, mn = x;
        else if (x < mn2) mn2 = x;
    }
    ll get(ll x) {
        ll ans = 0;
        if (x == mn) ans = mn2;
        else ans = mn;
        return ans == inf ? 0 : ans;
    }
} b[maxn];

int n;
ll a[maxn];
vector<int> edge[maxn];

ll ans, dp[maxn][2];
void predfs(int u, int ff) {
    dp[u][0] = dp[u][1] = a[u];
    int sz = 0;
    ll mx = -inf, mn = inf;
    for (int v: edge[u]) {
        if (v == ff) continue;
        predfs(v, u);
        sz++;
        mx = max(mx, dp[v][0]);
        mn = min(mn, dp[v][1]);
    }
    if (sz) {
        dp[u][0] += mn;
        dp[u][1] += mx;
    }
    dbg(u, dp[u][0], dp[u][1]);
}
ll rdp[maxn][2], fadp[maxn][2];
void dfs(int u, int ff) {
    ans = max(ans, rdp[u][0]);
    // b: mn, c: mx
    b[u].clear(); c[u].clear();
    for (int v: edge[u]) {
        if (v == ff) {
            b[u].insert(fadp[u][0]);
            c[u].insert(fadp[u][1]);
            continue;
        }
        b[u].insert(dp[v][1]);
        c[u].insert(dp[v][0]);
    }

    for (int v: edge[u]) {
        if (v == ff) continue;

        fadp[v][1] = a[u] + b[u].get(dp[v][1]);
        rdp[v][1] = a[v] + max(dp[v][1] - a[v], fadp[v][1]);

        fadp[v][0] = a[u] + c[u].get(dp[v][0]);
        rdp[v][0] = a[v];
        if ((int)edge[v].size() == 1) rdp[v][0] += fadp[v][0];
        else rdp[v][0] += min(dp[v][0] - a[v], fadp[v][0]);

        dfs(v, u);
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%lld", a + i);
        for (int i = 1; i <= n; i++) {
            edge[i].clear();
            ll x; scanf("%lld", &x); a[i] -= x;
        }
        for (int i = 2, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        predfs(1, 0);
        fadp[1][0] = fadp[1][1] = 0;
        rdp[1][0] = dp[1][0];
        rdp[1][1] = dp[1][1];
        ans = -inf;
        dfs(1, 0);
        printf("%lld\n", ans);
    }
    return 0;
}