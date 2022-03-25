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

int n, ans;
vector<int> edge[maxn];

struct Info {
    int mx, mx2;
    void clear() {
        mx = mx2 = 0;
    }
    void insert(int x) {
        if (x >= mx) mx2 = mx, mx = x;
        else if (x > mx2) mx2 = x;
    }
    int get(int x) {
        if (x == mx) return mx2;
        return mx;
    }
} a[maxn];

int f[maxn], g[maxn];
void predfs(int u, int ff) {
    int mx = -1;
    for (int v: edge[u]) {
        if (v == ff) continue;
        predfs(v, u);
        mx = max(mx, f[v]);
    }
    if (mx == -1) {
        f[u] = 1; return ;
    }
    f[u] = mx + (int)edge[u].size();
    if (u != 1) f[u]--;
    dbg(u, f[u]);
}
void dfs(int u, int ff) {
    a[u].clear();
    a[u].insert(g[u]);
    for (int v: edge[u]) {
        if (v == ff) continue;
        a[u].insert(f[v]);
    }
    int tot = 1 + a[u].mx + a[u].mx2;
    if ((int)edge[u].size() >= 3) tot += (int)edge[u].size() - 2;
    ans = max(ans, tot);
    
    for (int v: edge[u]) {
        if (v == ff) continue;
        g[v] = a[u].get(f[v]);
        dfs(v, u);
    }
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            edge[i].clear();
        }
        for (int i = 2, u, v; i <= n; i++) {
            scanf("%d%d", &u, &v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        ans = 1; g[1] = 0;
        predfs(1, 0);
        dfs(1, 0);
        printf("%d\n", ans);
    }
    return 0;
}