#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 5000 + 5;

struct MCMF {
    struct edge {
        int to, flow, cost, rev;
        edge() { }
        edge(int to, int f, int cost, int r): to(to), flow(f), cost(cost), rev(r) {}
    };
    int V, H[maxn + 5], dis[maxn + 5], preV[maxn + 5], preE[maxn + 5];
    vector<edge> G[maxn + 5];
    void init(int n) {
        V = n;
        for (int i = 0; i <= V; ++i) G[i].clear();
    }
    void add(int from, int to, int cap, int cost) {
        G[from].push_back(edge(to, cap, cost, (int)G[to].size()));
        G[to].push_back(edge(from, 0, -cost, (int)G[from].size() - 1));
    }
    int getmin(int s, int t, int f, int& flow) {
        int ans = 0; 
        fill(H, H + 1 + V, 0);
        while (f) {
            priority_queue<PII,vector<PII>,greater<PII> > q;
            fill(dis, dis + 1 + V, inf);
            dis[s] = 0; q.push({0, s});
            while (!q.empty()) {
                PII now = q.top(); q.pop();
                int v = now.second;
                if (dis[v] < now.first) continue;
                for (int i = 0; i < G[v].size(); ++i) {
                    edge& e = G[v][i];
                    if (e.flow > 0 && dis[e.to] > dis[v] + e.cost + H[v] - H[e.to]) {
                        dis[e.to] = dis[v] + e.cost + H[v] - H[e.to];
                        preV[e.to] = v;
                        preE[e.to] = i;
                        q.push({dis[e.to], e.to});
                    }
                }
            }
            if (dis[t] == inf) break;
            for (int i = 0; i <= V; ++i) H[i] += dis[i];
            int d = f;
            for (int v = t; v != s; v = preV[v]) d = min(d, G[preV[v]][preE[v]].flow);
            f -= d; flow += d; ans += d * H[t];
            for (int v = t; v != s; v = preV[v]) {
                edge& e = G[preV[v]][preE[v]];
                e.flow -= d;
                G[v][e.rev].flow += d;
            }
        }
        return ans;
    }
} f;

int n, k, a[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        f.init(3 + n + n);
        f.add(1, 2, k, 0);
        for (int i = 1; i <= n; i++) {
            scanf("%d", a + i);
            f.add(2, 2 + i, 1, 0);
            f.add(2 + i, 2 + n + i, 1, -a[i]);
            f.add(2 + n + i, 3 + n + n, 1, 0);
        }
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (a[i] > a[j]) continue;
                f.add(2 + n + i, 2 + j, 1, 0);
            }
        }
        int flow = 0;
        printf("%d\n", -f.getmin(1, 3 + n + n, inf, flow));
    }
    return 0;
}