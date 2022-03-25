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
const int inf = 1 << 28;
const int maxn = 400 + 5;
const int maxq = 100000 + 5;

int n, m, q, a[maxn], rk[maxn], G[maxn][maxn], p[maxn];
vector<PII> edge[maxn];
int ans[maxq];

struct Query {
    int s, t, k, id;
    bool operator<(const Query& b) const {
        return k < b.k;
    }
};

void add(int u) {
    // dbg(u);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            G[i][j] = min(G[i][j], G[i][u] + G[u][j]);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    vector<int> lsh;
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        lsh.push_back(a[i]);
        for (int j = 1; j <= n; j++) G[i][j] = inf;
        G[i][i] = 0;
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    for (int i = 1; i <= n; i++) {
        rk[i] = lower_bound(lsh.begin(), lsh.end(), a[i]) - lsh.begin() + 1;
    }

    for (int i = 1, u, v, d; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &d);
        edge[u].push_back({v, d});
        edge[v].push_back({u, d});
        G[u][v] = G[v][u] = d;
    }

    scanf("%d", &q);
    vector<Query> ql, qr;
    for (int i = 1, s, t, k, tp; i <= q; i++) {
        scanf("%d%d%d%d", &s, &t, &k, &tp);
        if (tp == 0) ql.push_back({s, t, k, i});
        else qr.push_back({s, t, k, i});
    }
    sort(ql.begin(), ql.end()); sort(qr.begin(), qr.end());

    for (int i = 1; i <= n; i++) p[i] = i;
    sort(p + 1, p + 1 + n, [&](int x, int y) {
        return a[x] < a[y];
    });
    int tot = 0;
    for (auto& q: ql) {
        while (tot < n && rk[p[tot + 1]] <= q.k) {
            add(p[++tot]);
        }
        if (G[q.s][q.t] == inf) ans[q.id] = -1;
        else ans[q.id] = G[q.s][q.t];
    }

    for (int i = 1; i <= n; i++) {
        p[i] = i; rk[i] = (int)lsh.size() - rk[i] + 1;
        for (int j = 1; j <= n; j++) G[i][j] = inf;
        G[i][i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (auto& x: edge[i]) {
            G[i][x.first] = x.second;
        }
    }
    sort(p + 1, p + 1 + n, [&](int x, int y) {
        return a[x] > a[y];
    });
    tot = 0;
    for (auto& q: qr) {
        while (tot < n && rk[p[tot + 1]] <= q.k) {
            add(p[++tot]);
        }
        if (G[q.s][q.t] == inf) ans[q.id] = -1;
        else ans[q.id] = G[q.s][q.t];
    }

    for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
    return 0;
}