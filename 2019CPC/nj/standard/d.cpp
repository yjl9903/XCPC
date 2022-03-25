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
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, m;
vector<int> edge[maxn];

double f[maxn], g[maxn];
int vis[maxn];
void dfs(int u) {
    if (vis[u]) return ;
    vis[u] = 1;

    double k = 1.0 * (int)edge[u].size();
    f[u] = g[u] = 1 + 1.0 / k;
    
    double sumf = 0, sumg = 0;

    for (int v: edge[u]) {
        dfs(v);
        sumf += f[v];
        sumg += g[v];
    }

    g[u] += sumg / k;
    f[u] += (g[u] + sumf + sumg) / k;
    // f[u] = 1.0 + (sumf + sumg + 2) / k + 1 / k / k;
    // dbg(u, k, sumf, sumg, f[u], g[u]);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            vis[i] = 0;
            edge[i].clear();
        }
        for (int i = 1, u, v; i <= m; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
        }
        vis[n] = 1; f[n] = g[n] = 0;
        dfs(1);
        printf("%.2lf\n", f[1]);
    }
    return 0;
}