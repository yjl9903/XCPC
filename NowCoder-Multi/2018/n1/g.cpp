#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,ll> PII;
const int inf = 1 << 30;
const int mod = 1e9 + 7;
const int maxn = 100 + 5;

inline int lowbit(int x) { return x & -x; }

vector<int> edge[maxn];
int n, m, k;
PII f[1 << 11][maxn], g[1 << 11][maxn];
bool vis[maxn];

struct node {
    int to; PII d;
    bool operator<(const node& b) const {
        return d > b.d;
    }
};

inline PII add(PII a, PII b) {
    return { a.first + b.first, a.second * b.second % mod };
}
inline void update(PII& a, PII b) {
    if (b.first < a.first) {
        a = b;
    } else if (b.first == a.first) {
        a.second += b.second;
        if (a.second >= mod) a.second -= mod;
    }
}

int main() {
    while (scanf("%d%d%d", &n, &m, &k) == 3) {
        for (int i = 0; i <= n; i++) edge[i].clear(); ms(vis, 0);
        for (int i = 1, u, v; i <= m; i++) {
            scanf("%d%d", &u, &v); u--; v--;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        int ss = 1 << k;
        priority_queue<node> pq;
        for (int s = 0; s < ss; s++) for (int i = 0; i < n; i++) f[s][i] = g[s][i] = {inf, 0};
        for (int i = 0; i < k; i++) f[1 << i][i] = g[1 << i][i] = {0, 1};
        for (int s = 1; s < ss; s++) {
            for (int i = 0; i < n; i++) {
                for (int t = s; t; t = (t - 1) & s) {
                    if (lowbit(t) != lowbit(s)) continue;
                    update(g[s][i], add(f[t][i], g[s ^ t][i]));
                }
            }
            for (int i = 0; i < n; i++) {
                if (g[s][i].first != inf) pq.push({i, g[s][i]});
                vis[i] = 0;
            }
            while (!pq.empty()) {
                node tp = pq.top(); pq.pop();
                if (vis[tp.to]) continue;
                vis[tp.to] = 1;
                for (int& v: edge[tp.to]) {

                }
            }
        }
        printf("%lld\n", f[ss - 1][0].second);
    }
    return 0;
}