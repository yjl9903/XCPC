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

int n, k;
vector<PII> edge[maxn];

ll f[maxn], g[maxn];
// f: k-1, g: k
void dfs(int u, int ff) {
    f[u] = g[u] = 0;
    vector<ll> vec;
    for (auto& x: edge[u]) {
        int v = x.first, w = x.second;
        if (v == ff) continue;
        dfs(v, u);
        f[u] += g[v]; g[u] += g[v];
        vec.push_back(w + f[v] - g[v]);
    }
    sort(vec.rbegin(), vec.rend());
    for (int i = 0; i < (int)vec.size() && i < k; i++) {
        if (vec[i] <= 0) break;
        g[u] += vec[i];
        if (i + 1 < k) f[u] += vec[i];
    }
    dbg(u, f[u], g[u]);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++) edge[i].clear();
        for (int i = 2, u, v, w; i <= n; i++) {
            scanf("%d%d%d", &u, &v, &w);
            edge[u].push_back({v, w});
            edge[v].push_back({u, w});
        }
        dfs(1, 0);
        printf("%I64d\n", g[1]);
    }
    return 0;
}