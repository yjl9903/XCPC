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
const int maxn = 200000 + 5;

int n;
vector<int> edge[maxn];

int siz[maxn]; ll ans = 0, tot = 0;
void dfs1(int u, int f) {
    siz[u] = 1;
    for (int v: edge[u]) {
        if (v == f) continue;
        dfs1(v, u); siz[u] += siz[v];
    }
    tot += siz[u];
}
void dfs(int u, int f) {
    dbg(u, tot);
    ans = max(ans, tot);
    for (int& v: edge[u]) {
        if (v == f) continue;
        ll r = tot;
        tot += n - siz[v];
        int x = n - siz[v];
        tot -= n - x;
        dfs(v, u);
        tot = r;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2, u, v; i <= n; i++) {
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs1(1, 0); dfs(1, 0);
    cout << ans;
    return 0;
}