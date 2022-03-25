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

int n, pre[maxn], siz[maxn], root[maxn];
ll a[maxn];
vector<int> bag[100], edge[maxn];
vector<PII> eg;
int nn;

int dis[maxn], vis[maxn];
int dij(int s, int t) {
    for (int i = 1; i <= n; i++) dis[i] = inf, vis[i] = 0;
    dis[s] = 0;
    priority_queue<PII> pq; pq.push({0, s});
    while (!pq.empty()) {
        PII tp = pq.top(); pq.pop();
        int u = tp.second;
        if (vis[u]) continue;
        vis[u] = 1;
        for (int v: edge[u]) {
            if (vis[v]) continue;
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                pq.push({ -dis[v], v });
            }
        }
    }
    return dis[t];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%I64d", a + i);
        for (int j = 0; j <= 61; j++) {
            if (a[i] >> j & 1) {
                bag[j].push_back(i);
            }
        }
    }
    for (int i = 0; i <= 61; i++) {
        if ((int)bag[i].size() >= 3) 
            return puts("3"), 0;
        else if ((int)bag[i].size() == 2) {
            int u = bag[i][0];
            int v = bag[i][1];
            if (u > v) swap(u, v);
            eg.push_back({u, v});
        }
    }
    sort(eg.begin(), eg.end());
    eg.resize(unique(eg.begin(), eg.end()) - eg.begin());
    nn = (int)eg.size();
    int ans = inf;
    for (int i = 0; i < nn; i++) {
        for (int i = 1; i <= n; i++) edge[i].clear();
        for (int j = 0; j < nn; j++) if (i != j) {
            int u = eg[j].first, v = eg[j].second;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        int u = eg[i].first, v = eg[i].second;
        int d = dij(u, v);
        if (d < inf) {
            ans = min(ans, d + 1);
        }
    }
    if (ans == inf) puts("-1");
    else cout << ans;
    return 0;
}