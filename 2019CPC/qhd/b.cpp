#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
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
const int inf = 1 << 30;
const int maxn = 500000 + 5;

int n, w[maxn];
vector<int> edge[maxn];

ll a[maxn], ans, val[maxn];
void update(int i, int x) {
    for (; i < maxn; i += i & -i) a[i] += x;
}
ll query(int i = maxn - 1) {
    ll r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
}

struct Query {
    int dfn, w, sgn, id;
};
vector<Query> que, upd;
int tot;

void dfs(int u, int f, int d) {
    que.push_back({tot++, w[u], -1, u});
    upd.push_back({tot, w[u], 1, 0});
    ans += query(w[u] - 1);
    val[u] = d - query(w[u]);
    update(w[u], 1);
    for (int v: edge[u]) {
        if (v == f) continue;
        dfs(v, u, d + 1);
    }
    update(w[u], -1);
    que.push_back({tot, w[u], 1, u});
}

int main() {
    while (scanf("%d", &n) == 1) {
        ans = tot = 0; que.clear(); upd.clear();
        for (int i = 1; i <= n; i++) edge[i].clear(), val[i] = 0;
        for (int i = 1; i <= n; i++) scanf("%d", w + i);
        for (int i = 1, u, v; i < n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        dfs(1, 0, 0);
        int p = 0;
        for (auto& q: que) {
            while (p < n && upd[p].dfn <= q.dfn) {
                update(upd[p].w, upd[p].sgn); p++;
            }
            val[q.id] -= q.sgn * (query() - query(q.w));
        }
        for (p--; p >= 0; p--) update(upd[p].w, -upd[p].sgn);
        sort(val + 1, val + 1 + n);
        vector<ll> v;
        v.push_back(ans);
        for (int i = 1; i <= n; i++) {
            ans += val[i];
            v.push_back(ans + 1ll * i * (i - 1) / 2);
        }
        reverse(v.begin(), v.end());
        for (auto& x: v) printf("%lld\n", x);
    }
    return 0;
}