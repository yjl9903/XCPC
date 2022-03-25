#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
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

struct Edge {
    int from, to; ll cap, flow;
    Edge(int u, int v, ll c, ll f): from(u), to(v), cap(c), flow(f) {}
};

struct Dinic {
    int n, m, s, t;
    vector<Edge> edges;
    vector<int> G[maxn];
    bool vis[maxn];
    int dep[maxn], cur[maxn];
    void clear(int n) {
        this->n = n;
        for (int i = 0; i <= n; i++) G[i].clear();
        edges.clear();
    }
    void adde(int from, int to, ll cap) {
        dbg(from, to, cap);
        edges.emplace_back(from, to, cap, 0);
        edges.emplace_back(to, from, 0, 0);
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }
    bool bfs() {
        ms(vis, 0); ms(dep, 0);
        queue<int> q; q.push(s);
        dep[s] = 0; vis[s] = 1;
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int i = 0; i < G[x].size(); i++) {
                Edge& e = edges[G[x][i]];
                if (!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = 1;
                    dep[e.to] = dep[x] + 1;
                    q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    ll dfs(int x, ll a) {
        if (x == t || a == 0) return a;
        ll flow = 0, f;
        for (int& i = cur[x]; i < G[x].size(); i++) { 
            Edge& e = edges[G[x][i]];
            if (dep[x] + 1 == dep[e.to] && (f = dfs(e.to, min(a, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }
    ll get(int s, int t) {
        this->s = s, this->t = t;
        ll flow = 0;
        while (bfs()) {
            ms(cur, 0);
            flow += dfs(s, inf);
        }
        return flow;
    }
} f;

int n, cnt[maxn];

int main() {

    int T; scanf("%d", &T);
    while (T--) {
        f.clear(50);
        for (int i = 1; i <= 9; i++) {
            scanf("%d", cnt + i);
            // if (cnt[i] == 0) continue;
            // f.adde(1, i + 1, cnt[i]);
        }
        int cnt = 0;
        for (int i = 1; i <= 9; i++) {
            for (int j = i; i + j <= 9; j++) {
                // dbg(i, j);
                if (i == j) cnt++;
                else cnt += 2;
            }
        }
        printf("%lld\n", f.get(1, 50));
    }
    return 0;
}